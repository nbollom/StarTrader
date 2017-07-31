//
// Created by nbollom on 7/06/17.
//

#ifndef STARTRADER_JSONVALUE_H
#define STARTRADER_JSONVALUE_H

#include <string>
#include <stdexcept>
#include <memory>

namespace JSON {

    class Array;
    class Object;

    class Value {

    protected:
        Value() {};

    public:
        virtual ~Value() {}

        virtual std::shared_ptr<Value> Copy() = 0;

        virtual bool IsIterable() { return false; }
        virtual bool IsObject() { return false; }
        virtual bool IsArray() { return false; }
        virtual bool IsNull() { return false; }
        virtual bool IsString() { return false; }
        virtual bool IsNumber() { return false; }
        virtual bool IsBool() { return false; }

        virtual std::shared_ptr<Object> AsObject() { throw std::runtime_error("Invalid type cast"); }
        virtual std::shared_ptr<Array> AsArray() { throw std::runtime_error("Invalid type cast"); }

        virtual std::wstring StringValue() = 0;
        virtual double NumberValue() = 0;
        virtual bool BooleanValue() = 0;
    };

}

#endif //STARTRADER_JSONVALUE_H
