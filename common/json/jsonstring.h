//
// Created by Nathan Bollom on 14/06/2017.
//

#ifndef STARTRADER_JSONSTRING_H
#define STARTRADER_JSONSTRING_H

#include "jsonvalue.h"

namespace JSON {

    class String : public Value {

    private:
        std::wstring _value;

    public:
        String();
        String(std::wstring string);
        String(std::shared_ptr<String> other);
        virtual ~String();

        std::shared_ptr<Value> Copy() override;

        bool IsString() override;
        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;
    };

}

#endif //STARTRADER_JSONSTRING_H
