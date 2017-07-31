//
// Created by nbollom on 7/06/17.
//

#ifndef STARTRADER_JSON_H
#define STARTRADER_JSON_H

#include <fstream>
#include "jsonvalue.h"
#include "jsoniterable.h"
#include "jsonarray.h"
#include "jsonobject.h"
#include "jsonnull.h"
#include "jsonstring.h"
#include "jsonboolean.h"
#include "jsonnumber.h"
#include "jsonparsestream.h"

namespace JSON {

    class Document {

    private:
        std::shared_ptr<Iterable> _root;

        static std::shared_ptr<Document> ParseDocument(JSONParseStream *source);
        static std::shared_ptr<Object> ParseObject(JSONParseStream *source);
        static std::shared_ptr<Array> ParseArray(JSONParseStream *source);
        static std::shared_ptr<Value> ParseValue(JSONParseStream *source);
        static std::shared_ptr<String> ParseString(JSONParseStream *source);
        static std::shared_ptr<Number> ParseNumber(JSONParseStream *source);
        static std::shared_ptr<Boolean> ParseBoolean(JSONParseStream *source);
        static std::shared_ptr<Null> ParseNull(JSONParseStream *source);

    public:
        Document();
        Document(std::shared_ptr<Iterable> root);
        Document(std::shared_ptr<Document> other);

        virtual ~Document();

        std::shared_ptr<Iterable> GetRoot();

        std::shared_ptr<Object> AsObject();
        std::shared_ptr<Array> AsArray();

        static std::shared_ptr<Document> Parse(std::wstring string);
        static std::shared_ptr<Document> Parse(std::wifstream &stream);
    };

}

#endif //STARTRADER_JSON_H
