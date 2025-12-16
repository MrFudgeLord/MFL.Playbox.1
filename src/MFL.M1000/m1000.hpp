#pragma once

#include "..\device.hpp"
// decoders
#include "..\MFL.B1002\b1002.hpp"
#include "..\MFL.B1004\b1004.hpp"
// buses and lines
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
// sockets and ports
#include "..\MFL.B3000\b3000.hpp"
#include "..\MFL.B3050\b3050.hpp"
#include "..\MFL.B3100\b3100.hpp"
#include "..\MFL.B3800\b3800.hpp"
#include "..\MFL.B3900\b3900.hpp"

class alignas(64) M1000 : public device {
public:
    B3000 *CPU;
    B3050 *VDP;
    B3100 *workRAM_1;
    B3100 *workRAM_2;
    B3100 *workRAM_3;
    B3100 *workRAM_4;
    B3100 *videoRAM_1;
    B3100 *videoRAM_2;
    B3100 *videoRAM_3;
    B3800 *controller;
    B3900 *cartridge;
public:
    B2000 dataBus;
    B2100 addrBus;
    B2310 rwLine;
    B2310 nmiLine;
    B2310 irqLine;
    B2310 rstLine;
public:
    B1002<10> workRAMDecoder {&addrBus};
    B1002<10> videoRAMDecoder {&addrBus};
    B1004<12> memMapDecoder {&addrBus};
    B1004<8>  hwRegDecoder {&addrBus};
public:
    M1000(B3000 *c,
          B3050 *v,
          B3100 *wr1,
          B3100 *wr2,
          B3100 *wr3,
          B3100 *wr4,
          B3100 *vr1,
          B3100 *vr2,
          B3100 *vr3,
          B3800 *ctrl,
          B3900 *cart);
};
