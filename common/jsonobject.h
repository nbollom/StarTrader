//
// Created by Nathan Bollom on 7/06/2017.
//

#ifndef STARTRADER_JSONOBJECT_H
#define STARTRADER_JSONOBJECT_H

#include <map>
#include <string>
#include "jsoniterable.h"

namespace JSON {

    class Object : public Iterable {

    private:
        std::map<std::wstring, std::shared_ptr<Value>> _map;

    public:
        Object();
        Object(std::shared_ptr<Object> other);
        Object(std::map<std::wstring, std::shared_ptr<Value>> map);
        virtual ~Object();

        std::shared_ptr<Value> Copy() override;

        bool HasKey(std::wstring key);
        uint64_t Length() override;

        std::shared_ptr<Object> AsObject() override;

        std::shared_ptr<Value> operator[] (std::wstring key);

        bool IsObject() override;

        std::wstring StringValue() override;
        double NumberValue() override;
        bool BooleanValue() override;

        typedef std::map<std::wstring, std::shared_ptr<Value>>::iterator object_iterator;

        Object::object_iterator object_begin();
        Object::object_iterator object_end();

        void Add(std::wstring key, std::shared_ptr<Value> value);
        std::shared_ptr<Value> Get(std::wstring key);
        void Remove(std::wstring key);

    };

}

#endif //STARTRADER_JSONOBJECT_H
