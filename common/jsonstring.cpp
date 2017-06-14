//
// Created by Nathan Bollom on 14/06/2017.
//

#include "jsonstring.h"

namespace JSON {

    String::String() {

    }

    String::String(std::wstring string) : _value(string) {

    }

    String::String(std::shared_ptr<String> other) {
        _value = other->StringValue();
    }

    String::~String() {

    }

    std::shared_ptr<Value> String::Copy() {
        return std::make_shared<String>(_value);
    }

    bool String::IsString() {
        return true;
    }

    std::wstring String::StringValue() {
        return _value;
    }

    double String::NumberValue() {
        return std::wcstod(_value.c_str(), nullptr);
    }

    bool String::BooleanValue() {
        return (bool)NumberValue();
    }

}
