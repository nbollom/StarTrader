//
// Created by Nathan Bollom on 27/07/2017.
//

#ifndef STARTRADER_RESOURCE_H
#define STARTRADER_RESOURCE_H

#include <string>
#include <memory>

class ResourceManager {

private:
    std::string base_path;

    std::string MakeAbsolutePath(const std::string &path);

public:
    ResourceManager(const std::string &path = "");
    std::ifstream GetIFStreamForPath(const std::string &path);
    std::wifstream GetWIFStreamForPath(const std::string &path);

};

void InitResources(const std::string path);
std::shared_ptr<ResourceManager> Resources();

#endif //STARTRADER_RESOURCE_H
