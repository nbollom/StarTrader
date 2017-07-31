//
// Created by Nathan Bollom on 7/06/2017.
//

#include "jsonarray.h"
#include "jsonobject.h"

namespace JSON {

    Array::Array() {

    }

    Array::Array(std::shared_ptr<Array> other) {
        for (Array::array_iterator i = other->array_begin(); i != other->array_end(); ++i) {
            std::shared_ptr<Value> v = *i;
            _values.push_back(v->Copy());
        }
    }

    Array::Array(std::vector<std::shared_ptr<Value>> values) {
        _values = values;
    }

    Array::~Array() {
        _values.clear();
    }

    std::shared_ptr<Value> Array::Copy() {
        return std::make_shared<Array>(_values);
    }

    bool Array::HasIndex(uint64_t index) {
        return index < _values.size();
    }

    uint64_t Array::Length() {
        return _values.size();
    }

    std::shared_ptr<Array> Array::AsArray() {
        return std::make_shared<Array>(_values);
    }

    std::shared_ptr<Value> Array::operator[](uint64_t index) {
        return Get(index);
    }

    bool Array::IsArray() {
        return true;
    }

    std::wstring Array::StringValue() {
        return L"[Array]";
    }

    double Array::NumberValue() {
        return 1;
    }

    bool Array::BooleanValue() {
        return true;
    }

    Array::array_iterator Array::array_begin() {
        return _values.begin();
    }

    Array::array_iterator Array::array_end() {
        return _values.end();
    }

    void Array::PushFront(std::shared_ptr<Value> value) {
        _values.insert(_values.begin(), value);
    }

    void Array::PushBack(std::shared_ptr<Value> value) {
        _values.push_back(value);
    }

    std::shared_ptr<Value> Array::Get(uint64_t index) {
        return _values[index];
    }

    std::shared_ptr<Value> Array::PopFront() {
        std::shared_ptr<Value> value = _values.front();
        _values.erase(_values.begin());
        return value;
    }

    std::shared_ptr<Value> Array::PopBack() {
        std::shared_ptr<Value> value = _values.back();
        _values.pop_back();
        return value;
    }

}
