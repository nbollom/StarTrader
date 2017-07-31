//
// Created by Nathan Bollom on 27/07/2017.
//

#ifndef STARTRADER_CONFIGURATION_H
#define STARTRADER_CONFIGURATION_H

#include <memory>
#include "../json/json.h"

class ConfigurationManager {

private:
    std::shared_ptr<JSON::Document> config_doc;

public:
    ConfigurationManager(const std::string &path = "");
    std::shared_ptr<JSON::Value> GetValue(const std::wstring &path);
    std::wstring GetValueAsString(const std::wstring &path);

};

void InitConfig(const std::string &path);
std::shared_ptr<ConfigurationManager> Config();

#endif //STARTRADER_CONFIGURATION_H
