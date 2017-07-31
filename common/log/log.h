//
// Created by nbollom on 27/04/17.
//

#ifndef STARTRADER_LOGGING_H
#define STARTRADER_LOGGING_H

#include <ostream>
#include <fstream>

typedef enum {
    LogLevelDebug = 0,
    LogLevelInfo = 1,
    LogLevelWarning = 2,
    LogLevelError = 3
} LogLevels;

std::string LogLevelName(LogLevels level);
LogLevels LogLevelFromName(std::string level_str);

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};

class Logger {
#pragma mark Private Variables
private:
    LogLevels log_level;
    std::filebuf output_buffer;
    NullBuffer null_buffer;
    std::ostream log_stream;
    std::ostream null_stream;

#pragma mark Private Methods
private:

#pragma mark Constructor/Destructor
public:
    Logger();
    virtual ~Logger();


#pragma mark Public Methods
public:
    void Flush();

#pragma mark Accessors
    std::ostream* GetStream(LogLevels level);
    LogLevels LogLevel();
    void SetLogLevel(LogLevels level);
};

void LogInit(LogLevels level);
void LogSetLevel(LogLevels level);
void LogFlush();
void LogClose();
std::ostream* LogGetStream(LogLevels level);

#define debug *LogGetStream(LogLevelDebug)
#define info *LogGetStream(LogLevelInfo)
#define warning *LogGetStream(LogLevelWarning)
#define error *LogGetStream(LogLevelError)

#endif //STARTRADER_LOGGING_H
