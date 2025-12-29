#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "../cartFuncs.hpp"
#include "../../MFL.M1100/m1100.hpp"
#include "../../MFL.B1003/b1003.hpp"
#include "../../MFL.B1004/b1004.hpp"
#include "../../MFL.B1005/b1005.hpp"
#include "../../MFL.B1006/b1006.hpp"
#include "../../MFL.S2003/s2003.hpp"
#include "../../MFL.S2004/s2004.hpp"
#include "../../MFL.S2005/s2005.hpp"
#include "../../MFL.S2006/s2006.hpp"
#include <algorithm>

B3900 *cartV0::cartM1100(std::fstream &ROMFileStream, std::fstream &NVRAMFileStream) {
    struct {
        uint8_t chrROM;
        uint8_t prgROM_1;
        uint8_t prgROM_2;
        uint8_t prgROM_3;
        uint8_t prgROM_4;
        uint8_t prgROM_5;
    } components, types;

    enum type : uint8_t {
        ROM,
        RAM,
        NVRAM
    };

    ROMFileStream.read((char *) &components, sizeof(components));

    B3100 *chrROM;
    B3100 *prgROM_1;
    B3100 *prgROM_2;
    B3100 *prgROM_3;
    B3100 *prgROM_4;
    B3100 *prgROM_5;

    switch(components.chrROM) {
        case 0x03:
            chrROM       = new S2003;
            types.chrROM = ROM;
            break;
        case 0x04:
            chrROM       = new S2004;
            types.chrROM = ROM;
            break;
        case 0x05:
            chrROM       = new S2005;
            types.chrROM = ROM;
            break;
        case 0x06:
            chrROM       = new S2006;
            types.chrROM = ROM;
            break;
        case 0x43:
            chrROM       = new S2003;
            types.chrROM = RAM;
            break;
        case 0x44:
            chrROM       = new S2004;
            types.chrROM = RAM;
            break;
        case 0x45:
            chrROM       = new S2005;
            types.chrROM = RAM;
            break;
        case 0x46:
            chrROM       = new S2006;
            types.chrROM = RAM;
            break;
        case 0x83:
            chrROM       = new S2003;
            types.chrROM = NVRAM;
            break;
        case 0x84:
            chrROM       = new S2004;
            types.chrROM = NVRAM;
            break;
        case 0x85:
            chrROM       = new S2005;
            types.chrROM = NVRAM;
            break;
        case 0x86:
            chrROM       = new S2006;
            types.chrROM = NVRAM;
            break;
        case 0xF0:
            chrROM       = nullptr;
            types.chrROM = RAM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 chrROM type invalid");
            exit(3);
    }

    switch(components.prgROM_1) {
        case 0x03:
            prgROM_1       = new S2003;
            types.prgROM_1 = ROM;
            break;
        case 0x04:
            prgROM_1       = new S2004;
            types.prgROM_1 = ROM;
            break;
        case 0x05:
            prgROM_1       = new S2005;
            types.prgROM_1 = ROM;
            break;
        case 0x06:
            prgROM_1       = new S2006;
            types.prgROM_1 = ROM;
            break;
        case 0x43:
            prgROM_1       = new S2003;
            types.prgROM_1 = RAM;
            break;
        case 0x44:
            prgROM_1       = new S2004;
            types.prgROM_1 = RAM;
            break;
        case 0x45:
            prgROM_1       = new S2005;
            types.prgROM_1 = RAM;
            break;
        case 0x46:
            prgROM_1       = new S2006;
            types.prgROM_1 = RAM;
            break;
        case 0x83:
            prgROM_1       = new S2003;
            types.prgROM_1 = NVRAM;
            break;
        case 0x84:
            prgROM_1       = new S2004;
            types.prgROM_1 = NVRAM;
            break;
        case 0x85:
            prgROM_1       = new S2005;
            types.prgROM_1 = NVRAM;
            break;
        case 0x86:
            prgROM_1       = new S2006;
            types.prgROM_1 = NVRAM;
            break;
        case 0xF0:
            prgROM_1       = nullptr;
            types.prgROM_1 = ROM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_1 type invalid");
            exit(4);
    }

    switch(components.prgROM_2) {
        case 0x03:
            prgROM_2       = new S2003;
            types.prgROM_2 = ROM;
            break;
        case 0x04:
            prgROM_2       = new S2004;
            types.prgROM_2 = ROM;
            break;
        case 0x05:
            prgROM_2       = new S2005;
            types.prgROM_2 = ROM;
            break;
        case 0x06:
            prgROM_2       = new S2006;
            types.prgROM_2 = ROM;
            break;
        case 0x43:
            prgROM_2       = new S2003;
            types.prgROM_2 = RAM;
            break;
        case 0x44:
            prgROM_2       = new S2004;
            types.prgROM_2 = RAM;
            break;
        case 0x45:
            prgROM_2       = new S2005;
            types.prgROM_2 = RAM;
            break;
        case 0x46:
            prgROM_2       = new S2006;
            types.prgROM_2 = RAM;
            break;
        case 0x83:
            prgROM_2       = new S2003;
            types.prgROM_2 = NVRAM;
            break;
        case 0x84:
            prgROM_2       = new S2004;
            types.prgROM_2 = NVRAM;
            break;
        case 0x85:
            prgROM_2       = new S2005;
            types.prgROM_2 = NVRAM;
            break;
        case 0x86:
            prgROM_2       = new S2006;
            types.prgROM_2 = NVRAM;
            break;
        case 0xF0:
            prgROM_2       = nullptr;
            types.prgROM_2 = RAM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_2 type invalid");
            exit(5);
    }

    switch(components.prgROM_3) {
        case 0x03:
            prgROM_3       = new S2003;
            types.prgROM_3 = ROM;
            break;
        case 0x04:
            prgROM_3       = new S2004;
            types.prgROM_3 = ROM;
            break;
        case 0x05:
            prgROM_3       = new S2005;
            types.prgROM_3 = ROM;
            break;
        case 0x06:
            prgROM_3       = new S2006;
            types.prgROM_3 = ROM;
            break;
        case 0x43:
            prgROM_3       = new S2003;
            types.prgROM_3 = RAM;
            break;
        case 0x44:
            prgROM_3       = new S2004;
            types.prgROM_3 = RAM;
            break;
        case 0x45:
            prgROM_3       = new S2005;
            types.prgROM_3 = RAM;
            break;
        case 0x46:
            prgROM_3       = new S2006;
            types.prgROM_3 = RAM;
            break;
        case 0x83:
            prgROM_3       = new S2003;
            types.prgROM_3 = NVRAM;
            break;
        case 0x84:
            prgROM_3       = new S2004;
            types.prgROM_3 = NVRAM;
            break;
        case 0x85:
            prgROM_3       = new S2005;
            types.prgROM_3 = NVRAM;
            break;
        case 0x86:
            prgROM_3       = new S2006;
            types.prgROM_3 = NVRAM;
            break;
        case 0xF0:
            prgROM_3       = nullptr;
            types.prgROM_3 = RAM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_3 type invalid");
            exit(6);
    }

    switch(components.prgROM_4) {
        case 0x03:
            prgROM_4       = new S2003;
            types.prgROM_4 = ROM;
            break;
        case 0x04:
            prgROM_4       = new S2004;
            types.prgROM_4 = ROM;
            break;
        case 0x05:
            prgROM_4       = new S2005;
            types.prgROM_4 = ROM;
            break;
        case 0x06:
            prgROM_4       = new S2006;
            types.prgROM_4 = ROM;
            break;
        case 0x43:
            prgROM_4       = new S2003;
            types.prgROM_4 = RAM;
            break;
        case 0x44:
            prgROM_4       = new S2004;
            types.prgROM_4 = RAM;
            break;
        case 0x45:
            prgROM_4       = new S2005;
            types.prgROM_4 = RAM;
            break;
        case 0x46:
            prgROM_4       = new S2006;
            types.prgROM_4 = RAM;
            break;
        case 0x83:
            prgROM_4       = new S2003;
            types.prgROM_4 = NVRAM;
            break;
        case 0x84:
            prgROM_4       = new S2004;
            types.prgROM_4 = NVRAM;
            break;
        case 0x85:
            prgROM_4       = new S2005;
            types.prgROM_4 = NVRAM;
            break;
        case 0x86:
            prgROM_4       = new S2006;
            types.prgROM_4 = NVRAM;
            break;
        case 0xF0:
            prgROM_4       = nullptr;
            types.prgROM_4 = RAM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_4 type invalid");
            exit(7);
    }

    switch(components.prgROM_5) {
        case 0x03:
            prgROM_5       = new S2003;
            types.prgROM_5 = ROM;
            break;
        case 0x04:
            prgROM_5       = new S2004;
            types.prgROM_5 = ROM;
            break;
        case 0x05:
            prgROM_5       = new S2005;
            types.prgROM_5 = ROM;
            break;
        case 0x06:
            prgROM_5       = new S2006;
            types.prgROM_5 = ROM;
            break;
        case 0x43:
            prgROM_5       = new S2003;
            types.prgROM_5 = RAM;
            break;
        case 0x44:
            prgROM_5       = new S2004;
            types.prgROM_5 = RAM;
            break;
        case 0x45:
            prgROM_5       = new S2005;
            types.prgROM_5 = RAM;
            break;
        case 0x46:
            prgROM_5       = new S2006;
            types.prgROM_5 = RAM;
            break;
        case 0x83:
            prgROM_5       = new S2003;
            types.prgROM_5 = NVRAM;
            break;
        case 0x84:
            prgROM_5       = new S2004;
            types.prgROM_5 = NVRAM;
            break;
        case 0x85:
            prgROM_5       = new S2005;
            types.prgROM_5 = NVRAM;
            break;
        case 0x86:
            prgROM_5       = new S2006;
            types.prgROM_5 = NVRAM;
            break;
        case 0xF0:
            prgROM_5       = nullptr;
            types.prgROM_5 = RAM;
            break;
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 prgROM_5 type invalid");
            exit(8);
    }

    B3100 *lastUsableROM = nullptr;

    for(B3100 **rom : {&chrROM,
                       &prgROM_1,
                       &prgROM_2,
                       &prgROM_3,
                       &prgROM_4,
                       &prgROM_5}) {
        if(*rom) {
            B3100::info memInfo = (*rom)->getInfo();
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        }
        if(*rom) {
            lastUsableROM = *rom;
        }
    }

    B3100 *component;

    component = chrROM;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.chrROM == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.chrROM == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    component = prgROM_1;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.prgROM_1 == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.prgROM_1 == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    component = prgROM_2;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.prgROM_2 == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.prgROM_2 == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    component = prgROM_3;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.prgROM_3 == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.prgROM_3 == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    component = prgROM_4;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.prgROM_4 == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.prgROM_4 == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    component = prgROM_5;
    if(component) {
        B3100::info memInfo = component->getInfo();
        if(types.prgROM_5 == ROM) {
            ROMFileStream.read((char *) memInfo.memory, memInfo.size);
        } else if(types.prgROM_4 == NVRAM) {
            NVRAMFileStream.read((char *) memInfo.memory, memInfo.size);
            nvramComponents[nvramCount++] = {memInfo.memory, memInfo.size};
        }
        lastUsableROM = component;
    }

    if(lastUsableROM == nullptr) SDL_Log("No ROMs present\n");

    M1100 *cartMB    = new M1100;
    cartMB->chrROM   = chrROM;
    cartMB->prgROM_1 = prgROM_1;
    cartMB->prgROM_2 = prgROM_2;
    cartMB->prgROM_3 = prgROM_3;
    cartMB->prgROM_4 = prgROM_4;
    cartMB->prgROM_5 = prgROM_5;

    uint8_t signalLine;

    uint8_t leastMemGranularity = 0xFF;

    for(uint8_t t : {(chrROM) ? chrROM->getInfo().size >> 7 : 0xFF,
                     (prgROM_1) ? prgROM_1->getInfo().size >> 7 : 0xFF,
                     (prgROM_2) ? prgROM_2->getInfo().size >> 7 : 0xFF,
                     (prgROM_3) ? prgROM_3->getInfo().size >> 7 : 0xFF,
                     (prgROM_4) ? prgROM_4->getInfo().size >> 7 : 0xFF,
                     (prgROM_5) ? prgROM_5->getInfo().size >> 7 : 0xFF}) {
        leastMemGranularity = std::min(leastMemGranularity, t);
    }

    switch(leastMemGranularity) {
        case 1 << 3: // 1 KB, 6 bits to 64 signals
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
        case 1 << 4: // 2 KB, 5 bits to 32 signals
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
        case 1 << 5: // 4 KB, 4 bits to 16 signals
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
        case 1 << 6: // 8 KB, 3 bits to 8 signals
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
        default:
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "M1100 leastMemGranularity not in range");
            exit(2);
    }
    return cartMB;
}
