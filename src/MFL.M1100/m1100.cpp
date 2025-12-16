#include "m1100.hpp"

#include <iostream>

M1100::M1100(B3100 *chr, B3100 *prg1, B3100 *prg2, B3100 *prg3, B3100 *prg4, B3100 *prg5) {
    chrROM   = chr;
    prgROM_1 = prg1;
    prgROM_2 = prg2;
    prgROM_3 = prg3;
    prgROM_4 = prg4;
    prgROM_5 = prg5;

    ROMDecoder.signalDevices[0x0] = NULL;
    ROMDecoder.signalDevices[0x1] = NULL;
    ROMDecoder.signalDevices[0x2] = chrROM;
    ROMDecoder.signalDevices[0x3] = prgROM_1;
    ROMDecoder.signalDevices[0x4] = prgROM_2;
    ROMDecoder.signalDevices[0x5] = prgROM_3;
    ROMDecoder.signalDevices[0x6] = prgROM_4;
    ROMDecoder.signalDevices[0x7] = prgROM_5;
}

bool M1100::initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) {
    puts("\n M1100 INIT");
    asm volatile("push 0x12345678\n add rsp, 4");
    signalHandler = sh;
    dataBus       = d;
    addrBus       = a;
    rw            = crw;
    nmi           = cnmi;
    irq           = cirq;

    ROMDecoder.addrBus = addrBus;
    return true;
}

uint32_t M1100::signal() {
    puts("\n M1100 SIGNAL");
    ROMDecoder.signal();
    return 0;
}
