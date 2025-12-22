#include "main.hpp"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include <cstdio>

namespace scheduler {
extern processor *processorPtr;
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    atexit(SDL_Quit);

    if(argc < 2) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Not enough arguments!");
        exit(1);
    }
    std::string cartPath = argv[1];

    std::fstream cartFileStream(cartPath);
    uint8_t      mbType;
    cartFileStream.read((char *) &mbType, 1);

    B3900 *(*cartFuncs[256])(std::fstream &) = {
        &cartM1100,
    };

    B3900 *cartMB = cartFuncs[mbType](cartFileStream);

    C1000 CPU;
    S1003 workRAM_1;
    S1003 workRAM_2;
    S1003 workRAM_3;
    S1003 workRAM_4;
    S1003 videoRAM_1;
    S1003 videoRAM_2;
    S1003 videoRAM_3;
    V1000 VDP;
    P1000 controller;

    M1000 motherboard {
        &CPU,
        &VDP,
        &workRAM_1,
        &workRAM_2,
        &workRAM_3,
        &workRAM_4,
        &videoRAM_1,
        &videoRAM_2,
        &videoRAM_3,
        &controller,
        cartMB};

    SDL_Window   *window   = SDL_CreateWindow("MFL Playbox 1", 768, 720, SDL_WINDOW_BORDERLESS);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_Surface  *surface  = SDL_CreateSurface(768, 720, SDL_PIXELFORMAT_RGBA32);
    SDL_Texture  *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 768, 720);

    dummy dummyDevice {&motherboard, {window, renderer, surface, texture}};
    // scheduler::scheduleEvent({0, 1, 100});

    // ((M1100 *) cartMB)->prgROM_5->getInfo().memory[8191] = 0x01;
    //((M1100 *) cartMB)->prgROM_5->getInfo().memory[8190] = 0x22;
    // videoRAM_1.memory[0x0000]                            = 0x01;
    // videoRAM_3.memory[0x0000]                            = 0x00;
    // VDP.real.mem[0x00]                                   = 0x12;
    // VDP.real.mem[0x01]                                   = 18;

    scheduler::processorPtr->run();

    return 0;
}
