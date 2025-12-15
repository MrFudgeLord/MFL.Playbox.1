#pragma once

#include "..\device.hpp"
#include "..\MFL.B1002\b1002.hpp"
#include "..\MFL.B1004\b1004.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
#include "..\MFL.B3000\b3000.hpp"
#include "..\MFL.B3050\b3050.hpp"
#include "..\MFL.B3100\b3100.hpp"

class alignas(64) M1100 : public device {
public:
    B3000 *CPU;
    B3050 *VDP;
    B3100 *workRAM[4];
    B3100 *videoRAM[3];
public:
    B1002<10> workRAMDecoder {addrBus};
    B1002<10> videoRAMDecoder {addrBus};
    B1004<12> memMapDecoder {addrBus};
    B2000     dataBus;
    B2100     addrBus;
    B2310     rwLine;
    B2310     nmiLine;
    B2310     irqLine;
    B2310     rstLine;
public:
    M1100(B3000 *c, B3050 *v, B3100 *wr1, B3100 *wr2, B3100 *wr3, B3100 *wr4, B3100 *vr1, B3100 *vr2, B3100 *vr3);
};
