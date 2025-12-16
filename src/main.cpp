#include "main.hpp"
#include "SDL3/SDL_init.h"

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
    B3900 *cartMB;

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

    CPU.reset();
    workRAM_1.memory[0x0000] = 0x00;
    CPU.b                    = 0x69;
    CPU.i.p                  = 0x0000;
    CPU.FDE();

    return 0;
}
