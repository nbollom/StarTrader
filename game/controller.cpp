//
// Created by Nathan Bollom on 1/06/2017.
//

#include <iostream>
#include "controller.h"

Controller::Controller(int argc, const char * const *argv) {
    CommandLineProcessor cmd("StarTrader", "A Space trading/combat game", "0.1");
    cmd.AddOption('l', "log_level", "The level of logging to use", true, "[DEBUG, INFO, WARNING, ERROR]", "WARNING");
    cmd.AddOption('c', "config", "Use a different config file", true, "Path to the config file to use", "");
    cmd.AddOption('d', "data", "Use the following data directory instead of default", true, "Path to the data directory to use", "");
    try {
        if (!cmd.Parse(argc, argv)) {
            exit(0);
        }
    }
    catch (ParseException &err) {
        std::cout << err.what() << std::endl << err.GetExceptionMessage() << std::endl;
        throw std::runtime_error(err.what());
    }
    if (cmd.IsSet('d')) {
        InitResources(cmd.GetOptionValue('d'));
    }
    if (cmd.IsSet('c')) {
        InitConfig(cmd.GetOptionValue('c'));
    }
    std::string level_str;
    std::shared_ptr<ConfigurationManager> config = Config();
    if (cmd.IsSet('l')) {
        level_str = cmd.GetOptionValue('l');
    }
    else {
        std::wstring w_level = config->GetValueAsString(L"log_level");
        level_str = std::string(w_level.begin(), w_level.end());
    }
    try {
        LogLevels level = LogLevelFromName(level_str);
        LogInit(level);
    }
    catch (std::runtime_error &err) {
        LogInit(LogLevelWarning);
        error << "Unknown log level " << level_str << std::endl;
        throw err;
    }
    info << "Starting StarTrader" << std::endl;
}

Controller::~Controller() {

}

void Controller::Run() {
    InitGraphics();
    try {
        _quit = false;
        EventManager_Ptr event = MakeEventManager_Ptr();
        int width = 1920;
        int height = 1200;
        GetScreenSize(width, height);
        Window_Ptr win = MakeWindow_Ptr((int)(width * 0.8), (int)(height * 0.8), false);
        event->RegisterWindow(win);
        KeyMap_Ptr kmap = MakeKeyMap_Ptr();
        KeyEvent e('q', KeyModifierNone, KeyEventDown);
        std::function<void()> handler = [this](){
            Quit();
        };
        kmap->AddKeyHandler(e, handler);
        event->PushKeyMap(kmap);
        while (!_quit) {
            event->ProcessEvents(&_quit);
        }
        event->PopAllKeyMaps();
        win->Close();
    }
    catch (std::runtime_error &err) {
        error << err.what() << std::endl;
    }
    CloseGraphics();
    info << "Exiting StarTrader" << std::endl;
    LogClose();
}

void Controller::Quit() {
    debug << "Controller::Quit Called" << std::endl;
    _quit = true;
}
