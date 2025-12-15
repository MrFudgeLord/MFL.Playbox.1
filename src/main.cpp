#include "main.hpp"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Not enough arguments!");
        return 1;
    }
    std::string cartPath = argv[1];

    std::fstream cartFileStream(cartPath);
    uint8_t      mbType;
    cartFileStream.read((char *) &mbType, 1);
    signaledDevice *cartMB;

    C1000 CPU;
    S1003 workRAM_1;
    S1003 workRAM_2;
    S1003 workRAM_3;
    S1003 workRAM_4;
    S1003 videoRAM_1;
    S1003 videoRAM_2;
    S1002 videoRAM_3;
    V1000 VDP;

    M1000 MB {
        &CPU, &VDP, &workRAM_1, &workRAM_2, &workRAM_3, &workRAM_4, &videoRAM_1, &videoRAM_2, &videoRAM_3};

    return 0;
}
