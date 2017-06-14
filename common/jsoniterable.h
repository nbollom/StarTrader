//
// Created by Nathan Bollom on 7/06/2017.
//

#ifndef STARTRADER_JSONITERABLE_H
#define STARTRADER_JSONITERABLE_H

#include <vector>
#include <map>
#include <string>
#include "jsonvalue.h"

namespace JSON {

    class Iterable : public Value {

    protected:
        Iterable() {}

    public:
        virtual uint64_t Length() = 0;

        bool IsIterable() override { return true; }

    };

}

#endif //STARTRADER_JSONITERABLE_H
