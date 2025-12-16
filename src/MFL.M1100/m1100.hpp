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
#include "..\MFL.B3900\b3900.hpp"

class alignas(64) M1100 : public B3900 {
public:
    B3100 *chrROM;
    B3100 *prgROM;
public:
    B1002<10> workRAMDecoder {addrBusInt};
    B1002<10> videoRAMDecoder {addrBusInt};
    B1004<12> memMapDecoder {addrBusInt};
    // B2000     dataBus;
    B2100 addrBusInt;
    // B2310     rwLine;
    // B2310     nmiLine;
    // B2310     irqLine;
    // B2310     rstLine;
public:
    M1100(B3000 *c, B3050 *v, B3100 *wr1, B3100 *wr2, B3100 *wr3, B3100 *wr4, B3100 *vr1, B3100 *vr2, B3100 *vr3);
    bool initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) override;
};
