#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "cartFuncs.hpp"
#include "../MFL.M1100/m1100.hpp"
#include "../MFL.B1003/b1003.hpp"
#include "../MFL.B1004/b1004.hpp"
#include "../MFL.B1005/b1005.hpp"
#include "../MFL.B1006/b1006.hpp"
#include "../MFL.S2003/s2003.hpp"
#include "../MFL.S2004/s2004.hpp"
#include "../MFL.S2005/s2005.hpp"
#include "../MFL.S2006/s2006.hpp"
#include <algorithm>
#include <sal.h>

B3900 *cartM1100(std::fstream &cartFileStream) {
    struct {
        uint8_t chrROM_1;
        uint8_t prgROM_1;
        uint8_t prgROM_2;
        uint8_t prgROM_3;
        uint8_t prgROM_4;
        uint8_t prgROM_5;
    } types;
    cartFileStream.read((char *) &types, sizeof(types));

    B3100 *chrROM;
    B3100 *prgROM_1;
    B3100 *prgROM_2;
    B3100 *prgROM_3;
    B3100 *prgROM_4;
    B3100 *prgROM_5;

    uint8_t leastMemGranularity = 0xFF;

    for(uint8_t t : {types.chrROM_1,
                     types.prgROM_1,
                     types.prgROM_2,
                     types.prgROM_3,
                     types.prgROM_4,
                     types.prgROM_5}) {
        leastMemGranularity = std::min(leastMemGranularity, t);
    }

    leastMemGranularity += 7;

    switch(types.chrROM_1) {
        case 0x03:
            chrROM = new S2003;
            break;
        case 0x04:
            chrROM = new S2004;
            break;
        case 0x05:
            chrROM = new S2005;
            break;
        case 0x06:
            chrROM = new S2006;
            break;
        case 0xF0:
            chrROM = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 chrROM type invalid");
            exit(3);
    }

    switch(types.prgROM_1) {
        case 0x03:
            prgROM_1 = new S2003;
            break;
        case 0x04:
            prgROM_1 = new S2004;
            break;
        case 0x05:
            prgROM_1 = new S2005;
            break;
        case 0x06:
            prgROM_1 = new S2006;
            break;
        case 0xF0:
            prgROM_1 = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_1 type invalid");
            exit(4);
    }

    switch(types.prgROM_2) {
        case 0x03:
            prgROM_2 = new S2003;
            break;
        case 0x04:
            prgROM_2 = new S2004;
            break;
        case 0x05:
            prgROM_2 = new S2005;
            break;
        case 0x06:
            prgROM_2 = new S2006;
            break;
        case 0xF0:
            prgROM_2 = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_2 type invalid");
            exit(5);
    }

    switch(types.prgROM_3) {
        case 0x03:
            prgROM_3 = new S2003;
            break;
        case 0x04:
            prgROM_3 = new S2004;
            break;
        case 0x05:
            prgROM_3 = new S2005;
            break;
        case 0x06:
            prgROM_3 = new S2006;
            break;
        case 0xF0:
            prgROM_3 = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_3 type invalid");
            exit(6);
    }

    switch(types.prgROM_4) {
        case 0x03:
            prgROM_4 = new S2003;
            break;
        case 0x04:
            prgROM_4 = new S2004;
            break;
        case 0x05:
            prgROM_4 = new S2005;
            break;
        case 0x06:
            prgROM_4 = new S2006;
            break;
        case 0xF0:
            prgROM_4 = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_4 type invalid");
            exit(7);
    }

    switch(types.prgROM_5) {
        case 0x03:
            prgROM_5 = new S2003;
            break;
        case 0x04:
            prgROM_5 = new S2004;
            break;
        case 0x05:
            prgROM_5 = new S2005;
            break;
        case 0x06:
            prgROM_5 = new S2006;
            break;
        case 0xF0:
            prgROM_5 = nullptr;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_5 type invalid");
            exit(8);
    }

    B3100 *lastUsableROM;

    for(B3100 **rom : {&chrROM,
                       &prgROM_1,
                       &prgROM_2,
                       &prgROM_3,
                       &prgROM_4,
                       &prgROM_5}) {
        if(*rom) {
            B3100::info memInfo = (*rom)->getInfo();
            cartFileStream.read((char *) memInfo.memory, memInfo.size);
        }
        if(*rom) {
            lastUsableROM = *rom;
        }
    }

    M1100 *cartMB    = new M1100;
    cartMB->chrROM   = chrROM;
    cartMB->prgROM_1 = prgROM_1;
    cartMB->prgROM_2 = prgROM_2;
    cartMB->prgROM_3 = prgROM_3;
    cartMB->prgROM_4 = prgROM_4;
    cartMB->prgROM_5 = prgROM_5;

    uint8_t signalLine;

    switch(leastMemGranularity) {
        case 10: // 1 KB, 6 bits to 64 signals
            cartMB->ROMDecoder = (B3980 *) new B1006<10>;
            signalLine         = 16;
            for(B3100 **rom : {&chrROM,
                               &prgROM_1,
                               &prgROM_2,
                               &prgROM_3,
                               &prgROM_4,
                               &prgROM_5}) {
                if(*rom) {
                    for(int i = 0; i < (*rom)->getInfo().size >> 10; i++) {
                        ((B1006<10> *) cartMB->ROMDecoder)->signalDevices[signalLine] = *rom;
                        signalLine++;
                    }
                }
            }
            while(signalLine < 64) {
                ((B1006<10> *) cartMB->ROMDecoder)->signalDevices[signalLine] = lastUsableROM;
                signalLine++;
            }
            break;
        case 11: // 2 KB, 5 bits to 32 signals
            cartMB->ROMDecoder = (B3980 *) new B1005<11>;
            signalLine         = 8;
            for(B3100 **rom : {&chrROM,
                               &prgROM_1,
                               &prgROM_2,
                               &prgROM_3,
                               &prgROM_4,
                               &prgROM_5}) {
                if(rom) {
                    for(int i = 0; i < (*rom)->getInfo().size >> 11; i++) {
                        ((B1005<11> *) cartMB->ROMDecoder)->signalDevices[signalLine] = *rom;
                        signalLine++;
                    }
                }
            }
            while(signalLine < 32) {
                ((B1005<11> *) cartMB->ROMDecoder)->signalDevices[signalLine] = lastUsableROM;
                signalLine++;
            }
            break;
        case 12: // 4 KB, 4 bits to 16 signals
            cartMB->ROMDecoder = (B3980 *) new B1004<12>;
            signalLine         = 4;
            for(B3100 **rom : {&chrROM,
                               &prgROM_1,
                               &prgROM_2,
                               &prgROM_3,
                               &prgROM_4,
                               &prgROM_5}) {
                if(rom) {
                    for(int i = 0; i < (*rom)->getInfo().size >> 12; i++) {
                        ((B1004<12> *) cartMB->ROMDecoder)->signalDevices[signalLine] = *rom;
                        signalLine++;
                    }
                }
            }
            while(signalLine < 16) {
                ((B1004<12> *) cartMB->ROMDecoder)->signalDevices[signalLine] = lastUsableROM;
                signalLine++;
            }
            break;
        case 13: // 8 KB, 3 bits to 8 signals
            cartMB->ROMDecoder = (B3980 *) new B1003<13>;
            signalLine         = 2;
            for(B3100 **rom : {&chrROM,
                               &prgROM_1,
                               &prgROM_2,
                               &prgROM_3,
                               &prgROM_4,
                               &prgROM_5}) {
                if(rom) {
                    for(int i = 0; i < (*rom)->getInfo().size >> 13; i++) {
                        ((B1003<13> *) cartMB->ROMDecoder)->signalDevices[signalLine] = *rom;
                        signalLine++;
                    }
                }
            }
            while(signalLine < 8) {
                ((B1003<13> *) cartMB->ROMDecoder)->signalDevices[signalLine] = lastUsableROM;
                signalLine++;
            }
            break;
        case 0xF7: // No memory
            printf("No ROMs present\n");
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 leastMemGranularity not in range");
            exit(2);
    }
    return cartMB;
}
