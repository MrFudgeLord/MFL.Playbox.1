#include "m1000.hpp"

M1000::M1000(B3000 *c,
             B3050 *v,
             B3100 *wr1,
             B3100 *wr2,
             B3100 *wr3,
             B3100 *wr4,
             B3110 *vr1,
             B3110 *vr2,
             B3110 *vr3,
             B3800 *ctrl,
             B3900 *cart) {

    CPU        = c;
    VDP        = v;
    workRAM_1  = wr1;
    workRAM_2  = wr2;
    workRAM_3  = wr3;
    workRAM_4  = wr4;
    videoRAM_1 = vr1;
    videoRAM_2 = vr2;
    videoRAM_3 = vr3;
    controller = ctrl;
    cartridge  = cart;

    memMapDecoder.initialize(&addrBus);
    hwRegDecoder.initialize(&addrBus);

    memMapDecoder.signalDevices[0x00] = workRAM_1;
    memMapDecoder.signalDevices[0x01] = workRAM_2;
    memMapDecoder.signalDevices[0x02] = workRAM_3;
    memMapDecoder.signalDevices[0x03] = workRAM_4;
    memMapDecoder.signalDevices[0x04] = videoRAM_1;
    memMapDecoder.signalDevices[0x05] = videoRAM_2;
    memMapDecoder.signalDevices[0x06] = videoRAM_3;
    memMapDecoder.signalDevices[0x07] = videoRAM_3;
    for(int i = 0x08; i < 0x0c; i++) memMapDecoder.signalDevices[i] = &hwRegDecoder;
    for(int i = 0x0c; i < 0x10; i++) memMapDecoder.signalDevices[i] = nullptr;
    for(int i = 0x10; i < 0x40; i++) memMapDecoder.signalDevices[i] = cartridge;

    hwRegDecoder.signalDevices[0x0] = VDP;
    hwRegDecoder.signalDevices[0x1] = VDP;
    hwRegDecoder.signalDevices[0x2] = controller;
    hwRegDecoder.signalDevices[0x3] = nullptr;
    hwRegDecoder.signalDevices[0x4] = nullptr;
    hwRegDecoder.signalDevices[0x5] = nullptr;
    hwRegDecoder.signalDevices[0x6] = nullptr;
    hwRegDecoder.signalDevices[0x7] = nullptr;
    hwRegDecoder.signalDevices[0x8] = nullptr;
    hwRegDecoder.signalDevices[0x9] = nullptr;
    hwRegDecoder.signalDevices[0xa] = nullptr;
    hwRegDecoder.signalDevices[0xb] = nullptr;
    hwRegDecoder.signalDevices[0xc] = nullptr;
    hwRegDecoder.signalDevices[0xd] = nullptr;
    hwRegDecoder.signalDevices[0xe] = nullptr;
    hwRegDecoder.signalDevices[0xf] = nullptr;

    if(workRAM_1) workRAM_1->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_2) workRAM_2->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_3) workRAM_3->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_4) workRAM_4->initialize(&dataBus, &addrBus, &rwLine);

    if(CPU) c->initialize(&memMapDecoder,
                          &dataBus,
                          &addrBus,
                          &rwLine,
                          &nmiLine,
                          &irqLine,
                          &rstLine);

    if(videoRAM_1) videoRAM_1->initialize(&dataBus, &addrBus, &rwLine, &lockLine);
    if(videoRAM_2) videoRAM_2->initialize(&dataBus, &addrBus, &rwLine, &lockLine);
    if(videoRAM_3) videoRAM_3->initialize(&dataBus, &addrBus, &rwLine, &lockLine);

    if(VDP) v->initialize(&memMapDecoder, &dataBus, &addrBus, &rwLine, &lockLine, &nmiLine, &irqLine);

    if(controller) controller->initialize(&dataBus, &addrBus, &rwLine);

    if(cartridge) {
        cartridge->initialize(&memMapDecoder,
                              &dataBus,
                              &addrBus,
                              &rwLine,
                              &nmiLine,
                              &irqLine);
    }
}
