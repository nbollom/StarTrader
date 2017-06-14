//
// Created by nbollom on 18/05/17.
//

#ifndef STARTRADER_EVENTMANAGER_H
#define STARTRADER_EVENTMANAGER_H

#include <memory>
#include <list>
#include <vector>
#include "window.h"
#include "keymap.h"

class EventManager {
#pragma mark Private Variables
private:
    std::list<Window_Ptr> _open_windows;
    std::vector<KeyMap_Ptr> _keymap_stack;

#pragma mark Private Methods
private:

#pragma mark Constructor/Destructor
public:
    EventManager();

    virtual ~EventManager();

#pragma mark Public Methods
public:
    void RegisterWindow(Window_Ptr win);
    void UnregisterWindow(Window_Ptr win);
    void PushKeyMap(KeyMap_Ptr map);
    void PopKeyMap();
    void PopAllKeyMaps();
    void ProcessEvents(bool *quit);

#pragma mark Accessors
public:

};

typedef std::shared_ptr<EventManager> EventManager_Ptr;
#define MakeEventManager_Ptr std::make_shared<EventManager>

#endif //STARTRADER_EVENTMANAGER_H
