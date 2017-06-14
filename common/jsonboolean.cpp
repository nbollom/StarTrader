//
// Created by nbollom on 14/06/17.
//

#include "jsonboolean.h"

namespace JSON {

    Boolean::Boolean(bool value) : _value(value) {

    }

    Boolean::~Boolean() {

    }

    std::shared_ptr<Value> Boolean::Copy() {
        return _value ? True() : False();
    }

    std::shared_ptr<Boolean> Boolean::True() {
        static std::shared_ptr<Boolean> boolean = std::shared_ptr<Boolean>(new Boolean(true));
        return boolean;
    }

    std::shared_ptr<Boolean> Boolean::False() {
        static std::shared_ptr<Boolean> boolean = std::shared_ptr<Boolean>(new Boolean(false));
        return boolean;
    }

    bool Boolean::IsBool() {
        return true;
    }

    std::wstring Boolean::StringValue() {
        return _value ? L"true" : L"false";
    }

    double Boolean::NumberValue() {
        return _value;
    }

    bool Boolean::BooleanValue() {
        return _value;
    }

}
