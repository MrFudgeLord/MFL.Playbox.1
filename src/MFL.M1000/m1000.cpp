#include "m1000.hpp"

M1000::M1000() {
    workRAMDecoder.signalDevices[0] = &workRAM[0];
    workRAM[0].initialize();
    memBankDecoder.signalDevices[1] = &workRAM[1];
    workRAM[1].initialize();
    memBankDecoder.signalDevices[2] = &workRAM[2];
    workRAM[2].initialize();
    memBankDecoder.signalDevices[3] = &workRAM[3];
    workRAM[3].initialize();

    memMapDecoder.signalDevices[0] = &memBankDecoder;
}
