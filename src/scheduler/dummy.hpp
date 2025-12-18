#pragma once

#include "..\scheduledDevice.hpp"
#include "..\MFL.M1000\m1000.hpp"
#include "SDL3/SDL_render.h"

struct SDLContext {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Surface  *surface;
    SDL_Texture  *texture;
};

class dummy : public scheduledDevice {
    M1000     *mb;
    SDLContext context;
public:
    dummy(M1000 *mbptr, SDLContext sdl);
    bool dispatchEvent(uint8_t index, uint8_t data[4]) override;
private:
    void frameEnd(uint8_t data[4]);
    void debugger(uint8_t data[4]);
public:
    uint64_t lastFrameEndns;
    uint8_t *frameBuffer = new uint8_t[720 * 768 * 4];
};
