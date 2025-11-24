#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\MFL.B1002\b1002.hpp"
#include "..\MFL.B1004\b1004.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
#include "..\MFL.C1000\c1000.hpp"
#include "..\MFL.S1000\s1000.hpp"

class alignas(64) M1000 : public device {
public:
    B2000     dataBus;
    B2100     addrBus;
    B1002<14> memBankDecoder {addrBus};
    B1004<12> memMapDecoder {addrBus};
    S1000     workRAM[4];
    C1000     CPU;
};
