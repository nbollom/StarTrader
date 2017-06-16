//
// Created by nbollom on 7/06/17.
//

#include "json.h"
#include <sstream>

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
        return ParseDocument(&stream);
    }

    std::shared_ptr<Document> Document::Parse(std::wifstream stream) {
        return ParseDocument(&stream);
    }

    std::shared_ptr<Document> Document::ParseDocument(std::wistream *source) {
        wchar_t character;
        source->get(character);
        std::shared_ptr<Iterable> root = nullptr;
        while (!source->eof()) {
            switch (character) {
                case '{':
                    if (root != nullptr) {
                        //already parsed an item so invalid JSON
                        throw std::runtime_error("JSON Parse error: Multiple roots detected");
                    }
                    root = ParseObject(source);
                    break;
                case '[':
                    if (root != nullptr) {
                        //already parsed an item so invalid JSON
                        throw std::runtime_error("JSON Parse error: Multiple roots detected");
                    }
                    root = ParseArray(source);
                    break;
                WHITESPACE_CASES
                    break;
                default:
                    throw std::runtime_error("JSON Parse error: Invalid character at root level");
            }
            source->get(character);
        }
        if (root == nullptr) {
            throw std::runtime_error("JSON Parse error: Empty Document");
        }
        std::shared_ptr<Document> doc = std::make_shared<Document>(root);
        return doc;
    }

    std::shared_ptr<Object> Document::ParseObject(std::wistream *source) {
        wchar_t character;
        source->get(character);
        bool done = false;
        bool parsing_key = false;
        std::wstring key = L"";
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        while (!done && !source->eof()) {
            if (parsing_key && character != '"') {
                key += character;
            }
            switch (character) {
                case '"':
                    parsing_key = !parsing_key;
                    break;
                WHITESPACE_CASES
                    break;
                case ':':
                    {
                        std::shared_ptr<Value> value = ParseValue(source);
                        if (value == nullptr) {
                            throw std::runtime_error("JSON Parse error: Value Expected");
                        }
                        obj->Add(key, value);
                        key = L"";
                    }
                    break;
                case '}':
                    // End of object hit
                    if (key.length() > 0) {
                        throw std::runtime_error("JSON Parse error: Key has no associated value");
                    }
                    done = true;
                    break;
                default:
                    break;
            }
            if (!done) {
                source->get(character);
            }
        }
        if (!done) {
            throw std::runtime_error("JSON Parse error: Object is not closed");
        }
        return obj;
    }

    std::shared_ptr<Array> Document::ParseArray(std::wistream *source) {
        wchar_t character;
        source->get(character);
        bool done = false;
        std::shared_ptr<Array> array = std::make_shared<Array>();
        while (!done && !source->eof()) {
            switch (character) {
                WHITESPACE_CASES
                case ',':
                    break;
                case ']':
                    done= true;
                    break;
                default:
                    source->unget();
                    std::shared_ptr<Value> value = ParseValue(source);
                    if (value == nullptr) {
                        throw std::runtime_error("JSON Parse error: Value Expected");
                    }
                    array->PushBack(value);
            }
            if (!done) {
                source->get(character);
            }
        }
        if (!done) {
            throw std::runtime_error("JSON Parse error: Array is not closed");
        }
        return array;
    }

    std::shared_ptr<Value> Document::ParseValue(std::wistream *source) {
        return nullptr;
    }

}