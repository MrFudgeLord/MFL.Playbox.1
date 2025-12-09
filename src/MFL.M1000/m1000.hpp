#pragma once

#include "..\device.hpp"
#include "..\MFL.B1002\b1002.hpp"
#include "..\MFL.B1004\b1004.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
#include "..\MFL.C1000\c1000.hpp"
#include "..\MFL.S1001\s1001.hpp"
#include "..\MFL.S1003\s1003.hpp"
#include "..\MFL.V1000\v1000.hpp"

class alignas(64) M1000 : public device {
public:
    B1002<10> workRAMDecoder {addrBus};
    B1004<12> memMapDecoder {addrBus};
    B2000     dataBus;
    B2100     addrBus;
    B2310     rwBus;
    B2310     nmiBus;
    B2310     irqBus;
    B2310     rstBus;
    S1001     videoRAM3 {dataBus, addrBus, rwBus};
    S1003     workRAM1 {dataBus, addrBus, rwBus};
    S1003     workRAM2 {dataBus, addrBus, rwBus};
    S1003     workRAM3 {dataBus, addrBus, rwBus};
    S1003     workRAM4 {dataBus, addrBus, rwBus};
    S1003     videoRAM1 {dataBus, addrBus, rwBus};
    S1003     videoRAM2 {dataBus, addrBus, rwBus};
    C1000     CPU {memMapDecoder, dataBus, addrBus, rwBus, nmiBus, irqBus, rstBus};
    V1000     VDP {memMapDecoder, dataBus, addrBus, rwBus, nmiBus, irqBus};
    M1000();
};
