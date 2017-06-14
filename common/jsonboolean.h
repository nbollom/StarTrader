//
// Created by nbollom on 14/06/17.
//

#ifndef STARTRADER_JSONBOOLEAN_H
#define STARTRADER_JSONBOOLEAN_H

#include "jsonvalue.h"

namespace JSON {

    class Boolean : public Value {

    private:
        bool _value;

        Boolean(bool value);

    public:
        virtual ~Boolean();
        std::shared_ptr<Value> Copy() override;
        static std::shared_ptr<Boolean> True();
        static std::shared_ptr<Boolean> False();
        bool IsBool() override;

        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;

    };

}

#endif //STARTRADER_JSONBOOLEAN_H
