//
// Created by Nathan Bollom on 1/06/2017.
//

#include "controller.h"

Controller::Controller(CommandLineProcessor *cmd) {

}

Controller::~Controller() {

}

void Controller::Run() {
    InitGraphics();
    try {
        _quit = false;
        EventManager_Ptr event = MakeEventManager_Ptr();
        Window_Ptr win = MakeWindow_Ptr(1920, 1200, false);
        event->RegisterWindow(win);
        KeyMap_Ptr kmap = MakeKeyMap_Ptr();
        KeyEvent e('q', KeyModifierNone, KeyEventDown);
        kmap->AddKeyHandler(e, std::bind(&Controller::Quit, this));
        event->PushKeyMap(kmap);
        while (!_quit) {
            event->ProcessEvents(&_quit);
        }
        event->PopAllKeyMaps();
        win->Close();
    }
    catch (std::runtime_error *err) {
        error << err->what() << std::endl;
    }
    CloseGraphics();
}

void Controller::Quit() {
    debug << "Controller::Quit Called" << std::endl;
    _quit = true;
}
