#pragma once

#include "../scheduledDevice.hpp"
#include "../MFL.M1000/m1000.hpp"
#include "SDL3/SDL_render.h"

struct SDLContext {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Surface  *surface;
    SDL_Texture  *texture;
};

class dummy : public scheduledDevice {
    SDLContext context;
public:
    dummy(SDLContext sdl);
    uint64_t dispatchEvent(uint8_t index, uint8_t data[4]) override;
private:
    void frameEnd(uint8_t data[4]);
    void debugger(uint8_t data[4]);
public:
    uint64_t  lastFrameEndns;
    uint32_t *frameBuffer = new uint32_t[(240 * 3) * (256 * 3)] {}; // RGBA8888[240][3][256][3]: Array of 240 scanlines, each being 3 rows of 256 pixels, each having 3 subpixels
};
