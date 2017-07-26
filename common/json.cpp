//
// Created by nbollom on 7/06/17.
//

#include "json.h"
#include <sstream>
#include <cmath>
#include "jsonparseexception.h"

#define WHITESPACE_CASES case ' ': case '\t': case '\n':

namespace JSON {

    Document::Document() {

    }

    Document::Document(std::shared_ptr<Iterable> root) : _root(root) {

    }

    Document::Document(std::shared_ptr<Document> other) {
        _root = std::static_pointer_cast<Iterable, Value>(other->GetRoot()->Copy());
    }

    Document::~Document() {

    }

    std::shared_ptr<Iterable> Document::GetRoot() {
        return _root;
    }

    std::shared_ptr<Object> Document::AsObject() {
        if (!_root->IsObject()) {
            throw std::runtime_error("Invalid type cast");
        } else {
            return _root->AsObject();
        }
    }

    std::shared_ptr<Array> Document::AsArray() {
        if (!_root->IsArray()) {
            throw std::runtime_error("Invalid type cast");
        } else {
            return _root->AsArray();
        }
    }

    std::shared_ptr<Document> Document::Parse(std::wstring string) {
        std::wstringstream stream;
        stream << string;
        JSONParseStream *json_stream = new JSONParseStream(&stream);
        return ParseDocument(json_stream);
    }

    std::shared_ptr<Document> Document::Parse(std::wifstream stream) {
        JSONParseStream *json_stream = new JSONParseStream(&stream);
        return ParseDocument(json_stream);
    }

    std::shared_ptr<Document> Document::ParseDocument(JSONParseStream *source) {
        wchar_t character = source->get();
        std::shared_ptr<Iterable> root = nullptr;
        while (!source->eof()) {
            switch (character) {
                case '{':
                    if (root != nullptr) {
                        //already parsed an item so invalid JSON
                        throw JSONParseException("JSON parse error: Multiple roots detected", source);
                    }
                    root = ParseObject(source);
                    break;
                case '[':
                    if (root != nullptr) {
                        //already parsed an item so invalid JSON
                        throw JSONParseException("JSON parse error: Multiple roots detected", source);
                    }
                    root = ParseArray(source);
                    break;
                WHITESPACE_CASES
                    break;
                default:
                    throw JSONParseException("JSON parse error: Invalid character at root level", source);
            }
            character = source->get();
        }
        if (root == nullptr) {
            throw JSONParseException("JSON parse error: Empty document", source);
        }
        std::shared_ptr<Document> doc = std::make_shared<Document>(root);
        return doc;
    }

    std::shared_ptr<Object> Document::ParseObject(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        bool parsing_key = false;
        bool require_delimiter = false;
        std::wstring key = L"";
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        while (!done && !source->eof()) {
            if (parsing_key && character != '"') {
                key += character;
            }
            switch (character) {
                case '"':
                    if (require_delimiter) {
                        throw JSONParseException("JSON parse error: Missing comma", source);
                    }
                    parsing_key = !parsing_key;
                    break;
                WHITESPACE_CASES
                    break;
                case ':':
                    {
                        std::shared_ptr<Value> value = ParseValue(source);
                        if (value == nullptr) {
                            throw JSONParseException("JSON parse error: Value expected", source);
                        }
                        obj->Add(key, value);
                        key = L"";
                        require_delimiter = true;
                    }
                    break;
                case ',':
                    if (!require_delimiter) {
                        throw JSONParseException("JSON parse error: Missing key:value pair", source);
                    }
                    require_delimiter = false;
                    break;
                case '}':
                    // End of object hit
                    if (key.length() > 0) {
                        throw JSONParseException("JSON parse error: Key has no associated value", source);
                    }
                    done = true;
                    break;
                default:
                    break;
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: Object is not closed", source);
        }
        return obj;
    }

    std::shared_ptr<Array> Document::ParseArray(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        bool parsing_value = true;
        std::shared_ptr<Array> array = std::make_shared<Array>();
        while (!done && !source->eof()) {
            switch (character) {
                WHITESPACE_CASES
                    break;
                case ',':
                    if (parsing_value) {
                        throw JSONParseException("JSON parse error: Value expected", source);
                    }
                    parsing_value = true;
                    break;
                case ']':
                    done= true;
                    break;
                default:
                    if (!parsing_value) {
                        throw JSONParseException("JSON parse error: Missing comma", source);
                    }
                    source->unget();
                    std::shared_ptr<Value> value = ParseValue(source);
                    if (value == nullptr) {
                        throw JSONParseException("JSON parse error: Value expected", source);
                    }
                    array->PushBack(value);
                    parsing_value = false;
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: Array is not closed", source);
        }
        return array;
    }

    std::shared_ptr<Value> Document::ParseValue(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        std::shared_ptr<Value> value = nullptr;
        while (!done && !source->eof()) {
            character = (wchar_t)towlower((wint_t)character);
            switch (character) {
                WHITESPACE_CASES
                    break;
                case '{':
                    value = ParseObject(source);
                    done = true;
                    break;
                case '[':
                    value = ParseArray(source);
                    done = true;
                    break;
                case '"':
                    value = ParseString(source);
                    done = true;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '+': //positive
                case '-': //negative
                case '.': //fraction
                case 'e': //exponential
                    source->unget();
                    value = ParseNumber(source);
                    done = true;
                    break;
                case 't':
                case 'f':
                    source->unget();
                    value = ParseBoolean(source);
                    done = true;
                    break;
                case 'n':
                    source->unget();
                    value = ParseNull(source);
                    done = true;
                    break;
                default:
                    throw JSONParseException("JSON parse error: Value expected", source);
            }
            if (!done) {
                character = source->get();
            }
        }
        return value;
    }

    std::shared_ptr<String> Document::ParseString(JSONParseStream *source) {
        wchar_t character = source->get();
        wchar_t last_char = '\0';
        bool done = false;
        std::wstring string;
        std::shared_ptr<String> value = nullptr;
        while (!done && !source->eof()) {
            if (character == '"' && last_char != '\\') { // end of string if it wasn't escaped
                value = std::make_shared<String>(string);
                done = true;
            }
            else {
                string.push_back(character);
                last_char = character;
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: String not terminated", source);
        }
        return value;
    }

    std::shared_ptr<Number> Document::ParseNumber(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        std::wstring string;
        std::shared_ptr<Number> value = nullptr;
        while (!done && !source->eof()) {
            character = (wchar_t)towlower((wint_t)character);
            if ((character >= '0' && character <= '9') || character == '+' || character == '-' || character == '.' || character == 'e') {
                string.push_back(character);
            }
            else {
                source->unget();
                done = true;
                double double_value = std::wcstod(string.c_str(), nullptr);
                value = std::make_shared<Number>(double_value);
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: Invalid JSON", source);
        }
        return value;
    }

    std::shared_ptr<Boolean> Document::ParseBoolean(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        std::wstring string;
        std::shared_ptr<Boolean> value = nullptr;
        while (!done && !source->eof()) {
            character = (wchar_t)towlower((wint_t)character);
            if (character >= 'a' && character <= 'z') {
                string.push_back(character);
            }
            else {
                source->unget();
                done = true;
                if (string == L"true") {
                    value = Boolean::True();
                }
                else if (string == L"false") {
                    value = Boolean::False();
                }
                else {
                    throw JSONParseException("JSON parse error: Invalid string literal", source);
                }
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: Invalid string literal", source);
        }
        return value;
    }

    std::shared_ptr<Null> Document::ParseNull(JSONParseStream *source) {
        wchar_t character = source->get();
        bool done = false;
        std::wstring string;
        std::shared_ptr<Null> value = nullptr;
        while (!done && !source->eof()) {
            character = (wchar_t)towlower((wint_t)character);
            if (character >= 'a' && character <= 'z') {
                string.push_back(character);
            }
            else {
                source->unget();
                done = true;
                if (string == L"null") {
                    value = Null::NullPtr();
                }
                else {
                    throw JSONParseException("JSON parse error: Invalid string literal", source);
                }
            }
            if (!done) {
                character = source->get();
            }
        }
        if (!done) {
            throw JSONParseException("JSON parse error: Invalid string literal", source);
        }
        return value;
    }

}