//
// Created by Nathan Bollom on 27/07/2017.
//

#include "resource.h"
#include "../log/log.h"

#define MAX_PATH_SIZE 4089

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
#include <unistd.h>
#include <dirent.h>

#else
#include <direct.h>
#endif

std::string GetCWD() {
    char path[MAX_PATH_SIZE];
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    if (getcwd(path, sizeof(path)) == nullptr) {
        error << "Couldn't get cwd" << std::endl;
        throw std::runtime_error("Couldn't get cwd");
    }
#else
    if (_getcwd(path, sizeof(path)) == nullptr) {
        error << "Couldn't get cwd" << std::endl;
        throw std::runtime_error("Couldn't get cwd");
    }
#endif
    std::string string_path = path;
    return string_path;
}

bool ContainsDir(const std::string &path, const std::string &dir) {
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    DIR *dp = opendir(path.c_str());
    if (dp != nullptr) {
        struct dirent *ep;
        while ((ep = readdir(dp)) != nullptr) {
            if (std::string(ep->d_name) == dir && ep->d_type == DT_DIR) {
                return true;
            }
        }
        closedir(dp);
    }
    return false;
#else
    //TODO: Windows ContainsDir
#endif
}

bool ContainsFile(const std::string &path, const std::string &file) {
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    DIR *dp = opendir(path.c_str());
    if (dp != nullptr) {
        struct dirent *ep;
        while ((ep = readdir(dp)) != nullptr) {
            if (std::string(ep->d_name) == file && ep->d_type == DT_REG) {
                return true;
            }
        }
        closedir(dp);
    }
    return false;
#else
    //TODO: Windows ContainsFile
#endif
}

std::string JoinDirs(const std::string &path, const std::string &dir) {
    std::string new_path;
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    if (path.back() == '/') {
        return path + dir;
    }
    new_path = path + "/" + dir;
#else
    //TODO: windows join path
#endif
    return new_path;
}

std::string BackDir(const std::string &path) {
    std::string new_path = path;
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    if (new_path == "/") {
        return path;
    }
    unsigned long end = new_path.back() == '/' ? new_path.length() - 1 : new_path.length();
    unsigned long index = new_path.find_last_of('/', end);
    new_path = new_path.substr(0, index);
#else
    //TODO: windows back dir
#endif
    return new_path;
}



ResourceManager::ResourceManager(const std::string &path) {
    if (path.length() != 0) {
        base_path = path;
    } else {
        std::string current_path = GetCWD();
        if(!ContainsDir(current_path, "data")) {
            current_path = BackDir(current_path);
            if(ContainsDir(current_path, "data")) {
                current_path = JoinDirs(current_path, "data");
            } else {
                error << "Unable to find data directory";
                throw std::runtime_error("Unable to find data directory");
            }
        }
        base_path = current_path;
    }
}

std::string ResourceManager::MakeAbsolutePath(const std::string &path) {
    if (path.length() == 0) {
        return path;
    }
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix
    if (path.front() == '/') {
        return path;
    }
#elif
    //Windows is full path
#endif
    std::string abs_path = JoinDirs(base_path, path);
    return abs_path;
}

std::ifstream ResourceManager::GetIFStreamForPath(const std::string &path) {
    std::string abs_path = MakeAbsolutePath(path);
    return std::ifstream(abs_path);
}

std::wifstream ResourceManager::GetWIFStreamForPath(const std::string &path) {
    std::string abs_path = MakeAbsolutePath(path);
    return std::wifstream(abs_path);
}

std::shared_ptr<ResourceManager> resource_instance = nullptr;

void InitResources(const std::string path) {
    resource_instance = std::make_shared<ResourceManager>(path);
}

std::shared_ptr<ResourceManager> Resources() {
    if (resource_instance == nullptr) {
        resource_instance = std::make_shared<ResourceManager>();
    }
    return resource_instance;
}
