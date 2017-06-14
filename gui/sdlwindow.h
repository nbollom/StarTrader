//
// Created by nbollom on 18/05/17.
//

#ifndef STARTRADER_SDLWINDOW_H
#define STARTRADER_SDLWINDOW_H

#include "window.h"
#include <SDL.h>

class SDLWindow : public Window {

private:
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;

    void DestroyWindow();
    void CreateWindow();

public:
    SDLWindow(int width, int height, bool fullscreen);
    virtual ~SDLWindow();

    void Close() override;
    void Resize(int width, int height) override;
    void SetFullscreen(bool fullscreen) override;
    void ToggleFullscreen() override;

};

#endif //STARTRADER_SDLWINDOW_H
