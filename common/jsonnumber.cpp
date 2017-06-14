//
// Created by nbollom on 14/06/17.
//

#include "jsonnumber.h"

namespace JSON {

    Number::Number() {

    }

    Number::Number(double number) : _value(number) {

    }

    Number::Number(std::shared_ptr<Number> other) {
        _value = other->NumberValue();
    }

    Number::~Number() {

    }

    std::shared_ptr<Value> Number::Copy() {
        return std::make_shared<Number>(_value);
    }

    bool Number::IsNumber() {
        return true;
    }

    std::wstring Number::StringValue() {
        return std::to_wstring(_value);
    }

    double Number::NumberValue() {
        return _value;
    }

    bool Number::BooleanValue() {
        return (bool)_value;
    }

}
