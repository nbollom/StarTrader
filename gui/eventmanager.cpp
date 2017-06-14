//
// Created by nbollom on 18/05/17.
//

#define EVENTMANAGER_PRIVATE
#include "eventmanager.h"

#include <SDL.h>

#pragma mark Private Methods

#pragma mark Constructor/Destructor

EventManager::EventManager() {

}

EventManager::~EventManager() {

}

#pragma mark Public Methods

void EventManager::RegisterWindow(Window_Ptr win) {
    _open_windows.push_back(win);
}

void EventManager::UnregisterWindow(Window_Ptr win) {
    _open_windows.remove(win);
}

void EventManager::PushKeyMap(KeyMap_Ptr map) {
    _keymap_stack.push_back(map);
}

void EventManager::PopKeyMap() {
    _keymap_stack.pop_back();
}

void EventManager::PopAllKeyMaps() {
    _keymap_stack.empty();
}

void EventManager::ProcessEvents(bool *quit) {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *quit = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                SDL_Keysym key = event.key.keysym;
                KeyEvent e(key.sym, key.mod, event.type);
                std::vector<KeyMap_Ptr>::reverse_iterator i = _keymap_stack.rbegin();
                bool stop = false;
                while (!stop && i != _keymap_stack.rend()) {
                    KeyMap_Ptr map = *i;
                    std::function<void()> f = (*map)[e];
                    if (f) {
                        f();
                        stop = true;
                    } else if (!map->BubbleDown()) {
                        stop = true;
                    }
                    ++i;
                }
            }
                break;
            default:
                break;
        }
    }
}
