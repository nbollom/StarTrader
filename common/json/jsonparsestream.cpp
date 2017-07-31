//
// Created by nbollom on 22/06/17.
//

#include "jsonparsestream.h"

namespace JSON {

    JSONParseStream::JSONParseStream(std::wistream *source) : _source(source) {
        _line = 0;
        _characters.push_back(0);
    }

    wchar_t JSONParseStream::get() {
        wchar_t character = (wchar_t)_source->get();
        if (!_source->eof()) {
            if (character == '\n') {
                _line++;
                if (_characters.size() < _line + 1) {
                    _characters.push_back(0);
                }
                _characters[_line] = 0;
            }
            else {
                _characters[_line]++;
            }
        }
        return character;
    }

    void JSONParseStream::unget() {
        _source->unget();
        wchar_t character = (wchar_t)_source->peek();
        if (character != std::wistream::traits_type::eof()) {
            if (character == '\n') {
                _characters[_line] = 0;
                _line--;
            }
            else {
                _characters[_line]--;
            }
        }
    }

    bool JSONParseStream::eof() const {
        return _source->eof();
    }

    int JSONParseStream::line() {
        return _line;
    }

    int JSONParseStream::character() {
        return _characters[_line];
    }

}
