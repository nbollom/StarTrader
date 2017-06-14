//
// Created by nbollom on 24/05/17.
//

#ifndef STARTRADER_KEYMAP_H
#define STARTRADER_KEYMAP_H

#include <map>
#include <functional>
#include <memory>
#include <string>

struct KeyEvent {
    KeyEvent();
    KeyEvent(int32_t key, int modifier, int event);
    int32_t key;
    int modifier;
    int event;
};

bool operator<(const KeyEvent &lhs, const KeyEvent &rhs);

class KeyMap {

#pragma mark Private Variables
private:
    std::map<KeyEvent, std::function<void()>> _map;
    bool _bubble_down;

#pragma mark Private Methods
private:

#pragma mark Constructor/Destructor
public:
    KeyMap(bool bubble_down = false);

    virtual ~KeyMap();

#pragma mark Public Methods
public:
    void AddKeyHandler(const int32_t key, const int modifier, const int event, std::function<void()> handler);
    void AddKeyHandler(const struct KeyEvent event, std::function<void()> handler);
    std::function<void()> operator[](const KeyEvent event);

#pragma mark Accessors
public:
    bool BubbleDown() {
        return _bubble_down;
    };

};

extern const int KeyModifierNone;
extern const int KeyModifierLShift;
extern const int KeyModifierRShift;
extern const int KeyModifierLCTL;
extern const int KeyModifierRCTL;
extern const int KeyModifierLALT;
extern const int KeyModifierRALT;
extern const int KeyModifierLGUI;
extern const int KeyModifierRGUI;
extern const int KeyModifierNum;
extern const int KeyModifierCaps;
extern const int KeyModifierMode;

std::string LabelForModifier(int mod);

extern const int KeyEventDown;
extern const int KeyEventUp;

typedef std::shared_ptr<KeyMap> KeyMap_Ptr;
#define MakeKeyMap_Ptr std::make_shared<KeyMap>

#endif //STARTRADER_KEYMAP_H
