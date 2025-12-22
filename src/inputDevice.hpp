#pragma once

#include <cstdint>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_oldnames.h"
#include "signaledDevice.hpp"

struct keyboardEvent {
    uint32_t keycode;
    uint32_t mods;
    bool     keyUp;
    bool     repeat;
};

struct mouseMoveEvent {
    float absX;
    float relX;
    float absY;
    float relY;
};

struct mouseClickEvent {
    uint8_t button;
    uint8_t clicks;
    float   absX;
    float   absY;
};

struct mouseScrollEvent {
    float scroll;
    float absX;
    float absY;
};

class inputDevice {
public:
    virtual void handleKeyboard(keyboardEvent event)       = 0;
    virtual void handleMouseMove(mouseMoveEvent event)     = 0;
    virtual void handleMouseClick(mouseClickEvent event)   = 0;
    virtual void handleMouseScroll(mouseScrollEvent event) = 0;
    virtual void resetInput()                              = 0;
};
