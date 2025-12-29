#include "main.hpp"
#include "SDL3/SDL_init.h"

namespace scheduler {
extern processor *processorPtr;
}

std::fstream ROMFileStream;
std::fstream NVRAMFileStream;

void exitCleanup() {
    cartV0::storeNVRAM(NVRAMFileStream);
    SDL_Quit();
    printf("Cleaned up!");
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    atexit(exitCleanup);

    if(argc < 2) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Not enough arguments!");
        exit(1);
    } else if(argc == 2) {
        ROMFileStream.open(argv[1], std::ios::in | std::ios::binary);
    } else if(argc == 3) {
        ROMFileStream.open(argv[1], std::ios::in | std::ios::binary);
        NVRAMFileStream.open(argv[2], std::ios::in | std::ios::out | std::ios::binary);
    }

    uint8_t version;
    uint8_t mbType;
    ROMFileStream.read((char *) &version, 1);
    ROMFileStream.read((char *) &mbType, 1);

    B3900 *(*cartFuncs[256])(std::fstream &, std::fstream &) = {
        &cartV0::cartM1100,
    };

    B3900 *cartMB = cartFuncs[mbType](ROMFileStream, NVRAMFileStream);

    C1000 CPU;
    S1003 workRAM_1;
    S1003 workRAM_2;
    S1003 workRAM_3;
    S1003 workRAM_4;
    S1103 videoRAM_1;
    S1103 videoRAM_2;
    S1102 videoRAM_3;
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

    dummy dummyDevice {{window, renderer, surface, texture}};
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
