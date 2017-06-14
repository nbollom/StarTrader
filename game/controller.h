//
// Created by Nathan Bollom on 1/06/2017.
//

#ifndef STARTRADER_CONTROLLER_H
#define STARTRADER_CONTROLLER_H

#include <memory>
#include "../common/common.h"
#include "../gui/gui.h"
#include "world.h"

class Controller {

private:
    bool _quit;


public:
    Controller(CommandLineProcessor *cmd);
    ~Controller();

    void Run();
    void Quit();

};

typedef shared_ptr<Controller> ControllerPtr;
static inline ControllerPtr MakeController(CommandLineProcessor *cmd) {
    return make_shared<Controller>(cmd);
}

#endif //STARTRADER_CONTROLLER_H
