#pragma once

#include "..\MFL.B1003\b1003.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"
#include "..\MFL.B3100\b3100.hpp"
#include "..\MFL.B3900\b3900.hpp"

class alignas(64) M1100 : public B3900 {
public:
    B3100 *chrROM;
    B3100 *prgROM_1;
    B3100 *prgROM_2;
    B3100 *prgROM_3;
    B3100 *prgROM_4;
    B3100 *prgROM_5;
public:
    B1003<13> ROMDecoder {NULL};
public:
    M1100(B3100 *chr, B3100 *prg1, B3100 *prg2, B3100 *prg3, B3100 *prg4, B3100 *prg5);
    bool     initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) override;
    uint32_t signal() override;
};
