//
// Created by nbollom on 18/05/17.
//

#include "sdlwindow.h"
#include <stdexcept>

SDLWindow::SDLWindow(int width, int height, bool fullscreen) : Window(width, height, fullscreen) {
    CreateWindow();
}

SDLWindow::~SDLWindow() {
    DestroyWindow();
}

void SDLWindow::DestroyWindow() {
    if (_renderer != nullptr) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window != nullptr) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}

void SDLWindow::CreateWindow() {
    DestroyWindow();
    Uint32 flags = 0;
    if (_fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_CreateWindowAndRenderer(_width, _height, flags, &_window, &_renderer)) {
        throw new std::runtime_error("Failed to initialise window");
    }
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void SDLWindow::Close() {
    DestroyWindow();
}

void SDLWindow::Resize(int width, int height) {
    if (_width != width && _height != height) {
        _width = width;
        _height = height;
        CreateWindow();
    }
}

void SDLWindow::SetFullscreen(bool fullscreen) {
    if (_fullscreen != fullscreen) {
        ToggleFullscreen();
    }
}

void SDLWindow::ToggleFullscreen() {
    _fullscreen = !_fullscreen;
    SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
}

Window_Ptr MakeWindow_Ptr(int width, int height, bool fullscreen) {
    SDLWindow *win = new SDLWindow(width, height, fullscreen);
    Window_Ptr ptr(win);
    return ptr;
}
