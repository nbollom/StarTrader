//
// Created by nbollom on 03/05/17.
//

#ifndef STARTRADER_COMMANDLINEOPTIONS_H
#define STARTRADER_COMMANDLINEOPTIONS_H

#include <string>

using namespace std;

class Option {

public:
    const char shortName;
    const string longName;
    const string description;
    const bool hasValue;
    const string valueDescription;
    bool found;
    string value;

    Option(const char shortName, const string longName, const string description, const bool hasValue, const string valueDescription, bool found, string value);
};

class ValueOption {

public:
    const string name;
    const string description;
    string value;

    ValueOption(const string name, const string description, string value);
};

#endif //STARTRADER_COMMANDLINEOPTIONS_H
