#include "main.hpp"
#include "MFL.S2006/s2006.hpp"
#include "SDL3/SDL_init.h"
#include <cstdio>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    printf("1");
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
    M1100 *cartMB = new M1100 {&chrROM_1, &prgROM_1, &prgROM_2, &prgROM_3, &prgROM_4, &prgROM_5};

    printf("\n M110 init: %p\n", &M1100::initialize);
    printf("B3900 init: %p\n", &B3900::initialize);

    printf("cartMB");

    C1000 CPU;
    printf("CPU");
    S1003 workRAM_1;
    S1003 workRAM_2;
    S1003 workRAM_3;
    S1003 workRAM_4;
    printf("workRAM");
    S1003 videoRAM_1;
    S1003 videoRAM_2;
    S1002 videoRAM_3;
    printf("videoRAM");
    V1000 VDP;
    printf("VDP");
    P1000 controller;
    printf("ctrl");

    M1000 motherboard {
        (B3000 *) &CPU,
        (B3050 *) &VDP,
        (B3100 *) &workRAM_1,
        (B3100 *) &workRAM_2,
        (B3100 *) &workRAM_3,
        (B3100 *) &workRAM_4,
        (B3100 *) &videoRAM_1,
        (B3100 *) &videoRAM_2,
        (B3100 *) &videoRAM_3,
        (B3800 *) &controller,
        (B3900 *) &cartMB};

    printf("mb");

    prgROM_5.memory[8191] = 0x01;
    puts("\n Memwrite 1");
    prgROM_5.memory[8190] = 0x22;
    puts("\n Memwrite 2");
    workRAM_1.memory[0x0122] = 0x00;
    puts("\n Memwrite 3");
    CPU.reset();
    puts("\n CPU Reset");
    CPU.b = 0x69;
    CPU.FDE();

    return 0;
}
