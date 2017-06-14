//
// Created by nbollom on 7/06/17.
//

#ifndef STARTRADER_JSON_H
#define STARTRADER_JSON_H

#include <functional>
#include <fstream>
#include "jsonvalue.h"
#include "jsoniterable.h"
#include "jsonarray.h"
#include "jsonobject.h"
#include "jsonnull.h"
#include "jsonstring.h"
#include "jsonboolean.h"
#include "jsonnumber.h"

namespace JSON {

    class Document : public Iterable {

    private:
        std::shared_ptr<Iterable> _root;

        static std::shared_ptr<Document> Parse(std::function<std::wstring()> source);

    public:
        Document();
        Document(std::shared_ptr<Iterable> root);
        Document(std::shared_ptr<Document> other);

        virtual ~Document();

        std::shared_ptr<Iterable> GetRoot();

        std::shared_ptr<Object> AsObject() override;
        std::shared_ptr<Array> AsArray() override;

        static std::shared_ptr<Document> Parse(std::wstring string);
        static std::shared_ptr<Document> Parse(std::wifstream stream);
    };

}

#endif //STARTRADER_JSON_H
