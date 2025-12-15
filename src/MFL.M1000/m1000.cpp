#include "m1000.hpp"

M1000::M1000(B3000 *c,
             B3050 *v,
             B3100 *wr1,
             B3100 *wr2,
             B3100 *wr3,
             B3100 *wr4,
             B3100 *vr1,
             B3100 *vr2,
             B3100 *vr3,
             B3800 *ctrl,
             B3900 *cart) {
    workRAM_1 = wr1;
    workRAM_2 = wr2;
    workRAM_3 = wr3;
    workRAM_4 = wr4;

    if(workRAM_1) workRAM_1->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_2) workRAM_2->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_3) workRAM_3->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_4) workRAM_4->initialize(&dataBus, &addrBus, &rwLine);

    CPU = c;
    c->initialize(&memMapDecoder,
                  &dataBus,
                  &addrBus,
                  &rwLine,
                  &nmiLine,
                  &irqLine,
                  &rstLine);

    VDP = v;
    v->initialize(&memMapDecoder, &dataBus, &addrBus, &rwLine, &nmiLine, &irqLine);

    videoRAM_1 = vr1;
    videoRAM_2 = vr2;
    videoRAM_3 = vr3;

    if(videoRAM_1) videoRAM_1->initialize(&dataBus, &addrBus, &rwLine);
    if(videoRAM_2) videoRAM_2->initialize(&dataBus, &addrBus, &rwLine);
    if(videoRAM_3) videoRAM_3->initialize(&dataBus, &addrBus, &rwLine);

    controller = ctrl;
    if(controller) controller->initialize(&dataBus, &addrBus, &rwLine);

    cartridge = cart;
    if(cartridge) cartridge->initialize(&memMapDecoder,
                                        &dataBus,
                                        &addrBus,
                                        &rwLine,
                                        &nmiLine,
                                        &irqLine);

    memMapDecoder.signalDevices[0x0] = &workRAMDecoder;
    memMapDecoder.signalDevices[0x1] = &videoRAMDecoder;
    memMapDecoder.signalDevices[0x2] = &hwRegDecoder;
    memMapDecoder.signalDevices[0x3] = NULL;
    memMapDecoder.signalDevices[0x4] = cartridge;
    memMapDecoder.signalDevices[0x5] = cartridge;
    memMapDecoder.signalDevices[0x6] = cartridge;
    memMapDecoder.signalDevices[0x7] = cartridge;
    memMapDecoder.signalDevices[0x8] = cartridge;
    memMapDecoder.signalDevices[0x9] = cartridge;
    memMapDecoder.signalDevices[0xa] = cartridge;
    memMapDecoder.signalDevices[0xb] = cartridge;
    memMapDecoder.signalDevices[0xc] = cartridge;
    memMapDecoder.signalDevices[0xd] = cartridge;
    memMapDecoder.signalDevices[0xe] = cartridge;
    memMapDecoder.signalDevices[0xf] = cartridge;
}
