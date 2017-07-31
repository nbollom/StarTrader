//
// Created by Nathan Bollom on 27/07/2017.
//

#include <sstream>
#include "configuration.h"
#include "../resource/resource.h"

ConfigurationManager::ConfigurationManager(const std::string &path) {
    std::string config_path = path;
    if (path.length() == 0) {
        config_path = "config.json";
    }
    std::wifstream stream = Resources()->GetWIFStreamForPath(config_path);
    config_doc = JSON::Document::Parse(stream);
    stream.close();
}

std::shared_ptr<JSON::Value> ConfigurationManager::GetValue(const std::wstring &path) {
    std::shared_ptr<JSON::Value> value = config_doc->GetRoot();
    std::wstringstream ss;
    ss.str(path);
    std::wstring item;
    while (std::getline(ss, item, L'.')) {
        if (!value->IsObject()) { //failed lookup, return NULL
            value = JSON::Null::NullPtr();
            break;
        }
        std::shared_ptr<JSON::Object> obj = std::dynamic_pointer_cast<JSON::Object>(value);
        if (!obj->HasKey(item)) {
            value = JSON::Null::NullPtr();
            break;
        }
        value = obj->Get(item);
    }
    return value;
}

std::wstring ConfigurationManager::GetValueAsString(const std::wstring &path) {
    std::shared_ptr<JSON::Value> value = GetValue(path);
    return value->StringValue();
}

std::shared_ptr<ConfigurationManager> config_instance = nullptr;

void InitConfig(const std::string &path) {
    config_instance = std::make_shared<ConfigurationManager>(path);
}

std::shared_ptr<ConfigurationManager> Config() {
    if (config_instance == nullptr) {
        config_instance = std::make_shared<ConfigurationManager>();
    }
    return config_instance;
}

