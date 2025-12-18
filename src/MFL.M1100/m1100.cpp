#include "m1100.hpp"
#include <cstdio>

bool M1100::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) {
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    nmi           = cnmi;
    irq           = cirq;

    ROMDecoder->initialize(addrBus);

    if(chrROM) chrROM->initialize(dataBus, addrBus, rw);
    if(prgROM_1) prgROM_1->initialize(dataBus, addrBus, rw);
    if(prgROM_2) prgROM_2->initialize(dataBus, addrBus, rw);
    if(prgROM_3) prgROM_3->initialize(dataBus, addrBus, rw);
    if(prgROM_4) prgROM_4->initialize(dataBus, addrBus, rw);
    if(prgROM_5) prgROM_5->initialize(dataBus, addrBus, rw);

    return true;
}

uint32_t M1100::signal() {
    ROMDecoder->signal();
    return 0;
}
