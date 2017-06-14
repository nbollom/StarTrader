//
// Created by nbollom on 7/06/17.
//

#include "json.h"

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
            return Value::AsObject();
        } else {
            return _root->AsObject();
        }
    }

    std::shared_ptr<Array> Document::AsArray() {
        if (!_root->IsArray()) {
            return Value::AsArray();
        } else {
            return _root->AsArray();
        }
    }

    std::shared_ptr<Document> Document::Parse(std::function<std::wstring()> source) {
        std::shared_ptr<Document> doc;
        std::wstring buff;
        bool clean = true;
        while (buff.length()) {
            buff = source();
        }
        if (!clean) {
            throw new std::runtime_error("JSON parse error");
        }
        return doc;
    }

    std::shared_ptr<Document> Document::Parse(std::wstring string) {
        uint64_t pos = 0;
        std::function<std::wstring(void)> source = [string, &pos]() {
            if (pos == string.length()) {
                return std::wstring(L"");
            }
            std::wstring str;
            uint64_t length = 512;
            if (string.length() < pos + length) {
                length = string.length() - pos;
            }
            str = string.substr(pos, length);
            pos = pos + length;
            return str;
        };
        return Parse(source);
    }

    std::shared_ptr<Document> Document::Parse(std::wifstream stream) {
        std::function<std::wstring(void)> source = [&stream]() {
            if (stream.eof()) {
                return std::wstring(L"");
            }
            else {
                wchar_t chars[512];
                stream.read(chars, 512);
                std::wstring str = chars;
                return str;
            }
        };
        return Parse(source);
    }

}