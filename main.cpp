#include <iostream>
#include "common/common.h"
#include "game/game.h"

int main(int argc, const char * const *argv) {
    CommandLineProcessor cmd("StarTrader", "A Space trading/combat game", "0.1");
    cmd.AddOption('l', "log_level", "The level of logging to use", true, "[DEBUG, INFO, WARNING, ERROR]", "WARNING");
    try {
        if (!cmd.Parse(argc, argv)) {
            return 0;
        }
    }
    catch (ParseException &err) {
        std::cout << err.what() << std::endl << err.GetExceptionMessage() << std::endl;
        return 1;
    }
    std::string level_str = cmd.GetOptionValue('l');
    try {
        LogLevels level = LogLevelFromName(level_str);
        LogInit(level);
    }
    catch (std::runtime_error &err) {
        LogInit(LogLevelWarning);
        error << "Unknown log level " << level_str << std::endl;
        return 1;
    }
    info << "Starting StarTrader" << std::endl;
    std::shared_ptr<JSON::Object> obj = std::make_shared<JSON::Object>();
    std::shared_ptr<JSON::Value> a = (*obj.get())[L"Test"];
    ControllerPtr controller = MakeController(&cmd);
    controller->Run();
    info << "Exiting StarTrader" << std::endl;
    LogClose();
    return 0;
}
