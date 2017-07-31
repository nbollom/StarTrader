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
    Controller(int argc, const char * const *argv);
    ~Controller();

    void Run();
    void Quit();

};

typedef shared_ptr<Controller> ControllerPtr;
static inline ControllerPtr MakeController(int argc, const char * const *argv) {
    return make_shared<Controller>(argc, argv);
}

#endif //STARTRADER_CONTROLLER_H
