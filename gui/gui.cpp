//
// Created by nbollom on 16/05/17.
//

#include "gui.h"
#include <SDL.h>

void InitGraphics() {
    SDL_Init(SDL_INIT_EVERYTHING);
}

void CloseGraphics() {
    SDL_Quit();
}
