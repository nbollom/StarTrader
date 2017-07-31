//
// Created by Nathan Bollom on 14/06/2017.
//

#include "jsonnull.h"

namespace JSON {

    Null::Null() {

    }

    Null::~Null() {

    }

    std::shared_ptr<Value> Null::Copy() {
        return NullPtr();
    }

    std::shared_ptr<Null> Null::NullPtr() {
        static std::shared_ptr<Null> null = std::shared_ptr<Null>(new Null());
        return null;
    }

    bool Null::IsNull() {
        return true;
    }

    std::wstring Null::StringValue() {
        return L"[NULL]";
    }

    double Null::NumberValue() {
        return 0;
    }

    bool Null::BooleanValue() {
        return false;
    }

}
