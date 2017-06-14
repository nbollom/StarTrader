//
// Created by Nathan Bollom on 7/06/2017.
//

#ifndef STARTRADER_JSONARRAY_H
#define STARTRADER_JSONARRAY_H

#include <vector>
#include "jsoniterable.h"

namespace JSON {

    class Array : public Iterable {

    private:
        std::vector<std::shared_ptr<Value>> _values;

    public:
        Array();
        Array(std::shared_ptr<Array> other);
        Array(std::vector<std::shared_ptr<Value>> values);
        virtual ~Array();

        std::shared_ptr<Value> Copy() override;

        bool HasIndex(uint64_t index);
        uint64_t Length() override;

        std::shared_ptr<Array> AsArray() override;

        std::shared_ptr<Value> operator[] (uint64_t index);

        bool IsArray() override;

        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;

        typedef std::vector<std::shared_ptr<Value>>::iterator array_iterator;

        Array::array_iterator array_begin();
        Array::array_iterator array_end();

        void PushFront(std::shared_ptr<Value> value);
        void PushBack(std::shared_ptr<Value> value);

        std::shared_ptr<Value> Get(uint64_t index);

        std::shared_ptr<Value> PopFront();
        std::shared_ptr<Value> PopBack();

    };

}

#endif //STARTRADER_JSONARRAY_H
