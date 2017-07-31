//
// Created by nbollom on 16/05/17.
//

#ifndef STARTRADER_WINDOW_H
#define STARTRADER_WINDOW_H

#include <memory>

class Window {

#pragma mark Protected Variables
protected:
    int _width;
    int _height;
    bool _fullscreen;

#pragma mark Private Methods
private:

#pragma mark Constructor/Destructor
protected:
    Window(int width, int height, bool fullscreen) : _width(width), _height(height), _fullscreen(fullscreen) {};

#pragma mark Public Methods
public:
    virtual void Close() = 0;
    virtual void Resize(int width, int height) = 0;
    virtual void SetFullscreen(bool fullscreen) = 0;
    virtual void ToggleFullscreen() = 0;

#pragma mark Accessors
public:

};

typedef std::shared_ptr<Window> Window_Ptr;
Window_Ptr MakeWindow_Ptr(int width, int height, bool fullscreen);

void GetScreenSize(int &width, int &height);

#endif //STARTRADER_WINDOW_H
