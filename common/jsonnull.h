//
// Created by Nathan Bollom on 14/06/2017.
//

#ifndef STARTRADER_JSONNULL_H
#define STARTRADER_JSONNULL_H

#include "jsonvalue.h"

namespace JSON {

    class Null : public Value {

    private:
        Null();

    public:
        virtual ~Null();
        std::shared_ptr<Value> Copy() override;
        static std::shared_ptr<Null> NullPtr();
        bool IsNull() override;

        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;
    };

}

#endif //STARTRADER_JSONNULL_H
