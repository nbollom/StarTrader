//
// Created by nbollom on 24/05/17.
//

#include "keymap.h"
#include <SDL.h>

KeyEvent::KeyEvent() {

}

KeyEvent::KeyEvent(int32_t key, int modifier, int event) : key(key), modifier(modifier), event(event) {

}

bool operator<(const KeyEvent &lhs, const KeyEvent &rhs) {
    if (lhs.key != rhs.key) {
        return lhs.key < rhs.key;
    }
    else if (lhs.modifier != rhs.modifier) {
        return lhs.modifier < rhs.modifier;
    }
    else {
        return lhs.event < rhs.event;
    }
}


KeyMap::KeyMap(bool bubble_down) : _bubble_down(bubble_down) {

}

KeyMap::~KeyMap() {

}


void KeyMap::AddKeyHandler(const int32_t key, const int modifier, const int event, std::function<void()> handler) {
    KeyEvent e(key, modifier, event);
    AddKeyHandler(e, handler);
}

void KeyMap::AddKeyHandler(const struct KeyEvent event, std::function<void()> handler) {
    _map[event] = handler;
}

std::function<void()> KeyMap::operator[](const KeyEvent event) {
    return _map[event];
}

const int KeyModifierNone = KMOD_NONE;
const int KeyModifierLShift = KMOD_LSHIFT;
const int KeyModifierRShift = KMOD_RSHIFT;
const int KeyModifierLCTL = KMOD_LCTRL;
const int KeyModifierRCTL = KMOD_RCTRL;
const int KeyModifierLALT = KMOD_LALT;
const int KeyModifierRALT = KMOD_RALT;
const int KeyModifierLGUI = KMOD_LGUI;
const int KeyModifierRGUI = KMOD_RGUI;
const int KeyModifierNum = KMOD_NUM;
const int KeyModifierCaps = KMOD_CAPS;
const int KeyModifierMode = KMOD_MODE;

#if defined(_WIN32) || defined(WIN32)
#define META_NAME "Win"
#elif defined(__APPLE__)
#define META_NAME "Cmd"
#else
#define META_NAME "Meta"
#endif

std::string LabelForModifier(int mod) {
    switch (mod) {
        case KeyModifierLShift:
            return "L-Shift";
        case KeyModifierRShift:
            return "R-Shift";
        case KeyModifierLCTL:
            return "L-CTL";
        case KeyModifierRCTL:
            return "R-CTL";
        case KeyModifierLALT:
            return "L-ALT";
        case KeyModifierRALT:
            return "R-ALT";
        case KeyModifierLGUI:
            return std::string("L-").append(META_NAME);
        case KeyModifierRGUI:
            return std::string("R-").append(META_NAME);
        case KeyModifierNum:
            return "Num";
        case KeyModifierCaps:
            return "Caps";
        case KeyModifierMode:
            return "ALT-GR";
        default:
            return "";
    }
}

const int KeyEventDown = SDL_KEYDOWN;
const int KeyEventUp = SDL_KEYUP;
