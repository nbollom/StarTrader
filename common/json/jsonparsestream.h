//
// Created by nbollom on 22/06/17.
//

#ifndef STARTRADER_JSONPARSESTREAM_H
#define STARTRADER_JSONPARSESTREAM_H

#include <istream>
#include <vector>

namespace JSON {

    class JSONParseStream {

    private:
        std::wistream *_source;
        int _line;
        std::vector<int> _characters;

    public:
        JSONParseStream(std::wistream *source);

        wchar_t get();
        void unget();
        bool eof() const;

        int line();
        int character();
    };

}

#endif //STARTRADER_JSONPARSESTREAM_H
