#include "m1000.hpp"
#include <cstdio>

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
    memMapDecoder.initialize(&addrBus);
    workRAMDecoder.initialize(&addrBus);
    videoRAMDecoder.initialize(&addrBus);
    hwRegDecoder.initialize(&addrBus);

    workRAM_1 = wr1;
    workRAM_2 = wr2;
    workRAM_3 = wr3;
    workRAM_4 = wr4;

    if(workRAM_1) workRAM_1->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_2) workRAM_2->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_3) workRAM_3->initialize(&dataBus, &addrBus, &rwLine);
    if(workRAM_4) workRAM_4->initialize(&dataBus, &addrBus, &rwLine);

    puts("\n MB WRAM INIT");

    CPU = c;

    if(CPU) c->initialize(&memMapDecoder,
                          &dataBus,
                          &addrBus,
                          &rwLine,
                          &nmiLine,
                          &irqLine,
                          &rstLine);

    puts("\n MB CPU INIT");

    videoRAM_1 = vr1;
    printf("\n %p", videoRAM_1);
    videoRAM_2 = vr2;
    printf("\n %p", videoRAM_2);
    videoRAM_3 = vr3;
    printf("\n %p", videoRAM_3);

    if(videoRAM_1) videoRAM_1->initialize(&dataBus, &addrBus, &rwLine);
    if(videoRAM_2) videoRAM_2->initialize(&dataBus, &addrBus, &rwLine);
    if(videoRAM_3) videoRAM_3->initialize(&dataBus, &addrBus, &rwLine);

    puts("\n MB VRAM INIT");

    VDP = v;

    if(VDP) v->initialize(&memMapDecoder, &dataBus, &addrBus, &rwLine, &nmiLine, &irqLine);

    puts("\n MB VDP INIT");

    controller = ctrl;

    if(controller) controller->initialize(&dataBus, &addrBus);

    puts("\n MB CTRL INIT");

    cartridge = cart;

    if(cartridge) {
        cartridge->initialize(&memMapDecoder,
                              &dataBus,
                              &addrBus,
                              &rwLine,
                              &nmiLine,
                              &irqLine);
    }

    puts("\n MB CART INIT");

    memMapDecoder.signalDevices[0x0] = &workRAMDecoder;
    memMapDecoder.signalDevices[0x1] = &videoRAMDecoder;
    memMapDecoder.signalDevices[0x2] = &hwRegDecoder;
    memMapDecoder.signalDevices[0x3] = nullptr;
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

    printf("\n MB MMD ASSIGN: %p", &memMapDecoder);

    workRAMDecoder.signalDevices[0x0] = workRAM_1;
    workRAMDecoder.signalDevices[0x1] = workRAM_2;
    workRAMDecoder.signalDevices[0x2] = workRAM_3;
    workRAMDecoder.signalDevices[0x3] = workRAM_4;

    printf("\n MB WRD ASSIGN: %p", &workRAMDecoder);

    videoRAMDecoder.signalDevices[0x0] = videoRAM_1;
    videoRAMDecoder.signalDevices[0x1] = videoRAM_2;
    videoRAMDecoder.signalDevices[0x2] = videoRAM_3;
    videoRAMDecoder.signalDevices[0x3] = videoRAM_3;

    printf("\n MB VRD ASSIGN: %p", &videoRAMDecoder);

    hwRegDecoder.signalDevices[0x0] = VDP;
    hwRegDecoder.signalDevices[0x1] = nullptr;
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
}
