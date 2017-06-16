//
// Created by nbollom on 27/04/17.
//

#include "log.h"
#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix file includes
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#endif //posix file includes

std::string LogLevelName(LogLevels level) {
    if (level == LogLevelDebug) {
        return "DEBUG";
    }
    else if (level == LogLevelInfo) {
        return "INFO";
    }
    else if (level == LogLevelWarning) {
        return "WARNING";
    }
    else if (level == LogLevelError) {
        return "ERROR";
    }
    else {
        throw std::runtime_error("Invalid logging level");
    }
}

LogLevels LogLevelFromName(std::string level_str) {
    std::string upper_str = level_str;
    std::transform(upper_str.begin(), upper_str.end(), upper_str.begin(), std::ptr_fun<int, int>(std::toupper));
    if (upper_str == "DEBUG") {
        return LogLevelDebug;
    }
    else if (upper_str == "INFO") {
        return LogLevelInfo;
    }
    else if (upper_str == "WARNING") {
        return LogLevelWarning;
    }
    else if (upper_str == "ERROR") {
        return LogLevelError;
    }
    else {
        throw std::runtime_error("Invalid logging level");
    }
}

Logger::Logger() : log_stream(&null_buffer), null_stream(&null_buffer) {
    log_level = LogLevelWarning;
#ifdef NDEBUG //use log file
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) //posix file utils
    std::string log_dir = getenv("HOME");
    if (log_dir.length() == 0) {
        log_dir = getpwuid(getuid())->pw_dir;
    }
    if (log_dir.back() != '/') {
        log_dir.push_back('/');
    }
    log_dir += ".config/startrader/";
    mkdir(log_dir.c_str(), 0775);
#else //windows code
    //todo: windows code to get log dr
#endif //posix file utils
    std::string log_file = log_dir + "startrader.log";
    if (output_buffer.open(log_file, std::ios::out)) {
        log_stream.rdbuf(&output_buffer);
    }
    else {
        //output to stderr instead
        log_stream.rdbuf(std::cerr.rdbuf());
        log_stream << "Failed to open log file " << log_file << std::endl;
    }
#else // Log to stderr
    log_stream.rdbuf(std::cerr.rdbuf());
#endif
}

Logger::~Logger() {
    if (output_buffer.is_open()) {
        output_buffer.close();
    }
}

void Logger::Flush() {
    log_stream.flush();
}

std::ostream* Logger::GetStream(LogLevels level) {
    if (level >= log_level) {
        std::time_t t = std::time(NULL);
        char date_string[100];
        if (std::strftime(date_string, sizeof(date_string), "%F %T", std::localtime(&t))) {
            log_stream << date_string << " [" << LogLevelName(level) << "]: ";
        }
        return &log_stream;
    }
    else {
        return &null_stream;
    }
}

void Logger::SetLogLevel(LogLevels level) {
    log_level = level;
}

LogLevels Logger::LogLevel() {
    return log_level;
}

Logger *instance = nullptr;

void LogInit(LogLevels level) {
    if (instance == nullptr) {
        instance = new Logger();
    }
    instance->SetLogLevel(level);
}

void LogSetLevel(LogLevels level) {
    if (instance == nullptr) {
        throw std::runtime_error("Log not initialised");
    }
    instance->SetLogLevel(level);
}

void LogFlush() {
    if (instance == nullptr) {
        throw std::runtime_error("Log not initialised");
    }
    instance->Flush();
}

void LogClose() {
    if (instance != nullptr) {
        instance->Flush();
        delete instance;
        instance = nullptr;
    }
}

std::ostream* LogGetStream(LogLevels level) {
    if (instance == nullptr) {
        throw std::runtime_error("Log not initialised");
    }
    return instance->GetStream(level);
}
