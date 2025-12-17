#include "main.hpp"
#include "MFL.S2006/s2006.hpp"
#include "SDL3/SDL_init.h"
#include "scheduler/scheduler.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    // if(argc < 2) {
    //     SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Not enough arguments!");
    //     return 1;
    // }
    // std::string cartPath = argv[1];

    // std::fstream cartFileStream(cartPath);
    // uint8_t      mbType;
    // cartFileStream.read((char *) &mbType, 1);
    S2006  chrROM_1;
    S2006  prgROM_1;
    S2006  prgROM_2;
    S2006  prgROM_3;
    S2006  prgROM_4;
    S2006  prgROM_5;
    B3900 *cartMB = new M1100 {&chrROM_1, &prgROM_1, &prgROM_2, &prgROM_3, &prgROM_4, &prgROM_5};

    C1000 CPU;
    S1003 workRAM_1;
    S1003 workRAM_2;
    S1003 workRAM_3;
    S1003 workRAM_4;
    S1003 videoRAM_1;
    S1003 videoRAM_2;
    S1002 videoRAM_3;
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

    dummy dummyDevice {&motherboard};
    scheduler::scheduleEvent({0, 1, 100});

    prgROM_5.memory[8191]    = 0x01;
    prgROM_5.memory[8190]    = 0x22;
    workRAM_1.memory[0x0122] = 0x00;
    workRAM_1.memory[0x0123] = 0x5c;
    CPU.reset();
    CPU.b = 0x69;
    CPU.run();

    return 0;
}
