#include "main.hpp"
#include <cstdio>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

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

    // ((M1100 *) cartMB)->prgROM_5->getInfo().memory[8191] = 0x01;
    // ((M1100 *) cartMB)->prgROM_5->getInfo().memory[8190] = 0x22;
    // workRAM_1.memory[0x0122]                             = 0x00;
    // workRAM_1.memory[0x0123]                             = 0x5c;
    CPU.reset();
    CPU.b = 0x69;
    CPU.run();

    return 0;
}
