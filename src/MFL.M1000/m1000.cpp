#include "m1000.hpp"

M1000::M1000() {
    memBankDecoder.signalDevices[0] = &workRAM[0];
    workRAM[0].initMemory();
    memBankDecoder.signalDevices[1] = &workRAM[1];
    workRAM[1].initMemory();
    memBankDecoder.signalDevices[2] = &workRAM[2];
    workRAM[2].initMemory();
    memBankDecoder.signalDevices[3] = &workRAM[3];
    workRAM[3].initMemory();

    memMapDecoder.signalDevices[0] = &memBankDecoder;
}
