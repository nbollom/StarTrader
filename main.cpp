#include "game/game.h"

int main(int argc, const char * const *argv) {
    try {
        ControllerPtr controller = MakeController(argc, argv);
        controller->Run();
    }
    catch (std::exception &err) {
        return 1;
    }
    return 0;
}
