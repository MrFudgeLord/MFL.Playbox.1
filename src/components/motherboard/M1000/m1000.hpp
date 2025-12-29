#pragma once

#include "../../../basicDeviceClasses/device.hpp"
// decoders
#include "../../decoders/B1004/b1004.hpp"
#include "../../decoders/B1006/b1006.hpp"
// buses and lines
#include "../../busses/B2000/b2000.hpp"
#include "../../busses/B2100/b2100.hpp"
#include "../../busses/B2310/b2310.hpp"
// sockets and ports
#include "../../sockets/processors/B3000/b3000.hpp"
#include "../../sockets/processors/B3050/b3050.hpp"
#include "../../sockets/storage/B3100/b3100.hpp"
#include "../../sockets/storage/B3110/b3110.hpp"
#include "../../sockets/peripherals/B3800/b3800.hpp"
#include "../../sockets/cartBoards/B3900/b3900.hpp"

class alignas(64) M1000 : public device {
public:
    B3000 *CPU;
    B3050 *VDP;
    B3100 *workRAM_1;
    B3100 *workRAM_2;
    B3100 *workRAM_3;
    B3100 *workRAM_4;
    B3110 *videoRAM_1;
    B3110 *videoRAM_2;
    B3110 *videoRAM_3;
    B3800 *controller;
    B3900 *cartridge;
public:
    B2000 dataBus;
    B2100 addrBus;
    B2310 rwLine;
    B2310 lockLine;
    B2310 nmiLine;
    B2310 irqLine;
    B2310 rstLine;
public:
    B1006<10> memMapDecoder;
    B1004<8>  hwRegDecoder;
public:
    M1000(B3000 *c,
          B3050 *v,
          B3100 *wr1,
          B3100 *wr2,
          B3100 *wr3,
          B3100 *wr4,
          B3110 *vr1,
          B3110 *vr2,
          B3110 *vr3,
          B3800 *ctrl,
          B3900 *cart);
};
