#include "m1000.hpp"

M1000::M1000() {
    workRAMDecoder.signalDevices[0] = &workRAM1;
    workRAM1.initialize();
    workRAMDecoder.signalDevices[1] = &workRAM2;
    workRAM2.initialize();
    workRAMDecoder.signalDevices[2] = &workRAM3;
    workRAM3.initialize();
    workRAMDecoder.signalDevices[3] = &workRAM4;
    workRAM4.initialize();

    memMapDecoder.signalDevices[0] = &workRAMDecoder;
    videoRAMDecoder.signalDevices[0] =
      memMapDecoder.signalDevices[1] = &videoRAMDecoder;
}
