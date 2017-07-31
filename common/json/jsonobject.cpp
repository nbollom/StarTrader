//
// Created by Nathan Bollom on 7/06/2017.
//

#include "jsonobject.h"
#include "jsonarray.h"

namespace JSON {

    Object::Object() {

    }

    Object::Object(std::shared_ptr<Object> other) {
        for (Object::object_iterator i = other->object_begin(); i != other->object_end(); ++i) {
            std::pair<std::wstring, std::shared_ptr<Value>> pair = *i;
            _map[pair.first] = pair.second->Copy();
        }
    }

    Object::Object(std::map<std::wstring, std::shared_ptr<Value>> map) : _map(map) {
    }

    Object::~Object() {
        _map.clear();
    }

    std::shared_ptr<Value> Object::Copy() {
        return std::make_shared<Object>(_map);
    }

    bool Object::HasKey(std::wstring key) {
        return _map[key] != nullptr;
    }

    uint64_t Object::Length() {
        return _map.size();
    }

    std::shared_ptr<Object> Object::AsObject() {
        return std::make_shared<Object>(_map);
    }

    std::shared_ptr<Value> Object::operator[](std::wstring key) {
        return Get(key);
    }

    bool Object::IsObject() {
        return true;
    }

    std::wstring Object::StringValue() {
        return L"[Object]";
    }

    double Object::NumberValue() {
        return 1;
    }

    bool Object::BooleanValue() {
        return true;
    }

    Object::object_iterator Object::object_begin() {
        return _map.begin();
    }

    Object::object_iterator Object::object_end() {
        return _map.end();
    }

    void Object::Add(std::wstring key, std::shared_ptr<Value> value) {
        _map[key] = value;
    }

    std::shared_ptr<Value> Object::Get(std::wstring key) {
        return _map[key];
    }

    void Object::Remove(std::wstring key) {
        std::shared_ptr<Value> value = _map[key];
        if (value != nullptr) {
            _map.erase(key);
        }
    }

}
