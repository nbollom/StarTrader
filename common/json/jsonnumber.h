//
// Created by nbollom on 14/06/17.
//

#ifndef STARTRADER_JSONNUMBER_H
#define STARTRADER_JSONNUMBER_H

#include "jsonvalue.h"

namespace JSON {

    class Number : public Value {

    private:
        double _value;

    public:
        Number();
        Number(double number);
        Number(std::shared_ptr<Number> other);
        virtual ~Number();

        std::shared_ptr<Value> Copy() override;

        bool IsNumber() override;
        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;
    };

}

#endif //STARTRADER_JSONNUMBER_H
