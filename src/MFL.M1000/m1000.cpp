#include "m1000.hpp"

M1000::M1000(B3000 *c, B3050 *v, B3100 *wr1, B3100 *wr2, B3100 *wr3, B3100 *wr4, B3100 *vr1, B3100 *vr2, B3100 *vr3) {
    CPU = c;
    c->initialize(&memMapDecoder, &dataBus, &addrBus, &rwLine, &nmiLine, &irqLine, &rstLine);

    VDP = v;
    v->initialize(&memMapDecoder, &dataBus, &addrBus, &rwLine, &nmiLine, &irqLine);

    workRAM[0] = wr1;
    workRAM[1] = wr2;
    workRAM[2] = wr3;
    workRAM[3] = wr4;

    for(B3100 *wr : workRAM) {
        if(wr) wr->initialize(&dataBus, &addrBus, &rwLine);
    }

    videoRAM[0] = vr1;
    videoRAM[1] = vr2;
    videoRAM[2] = vr3;

    for(B3100 *vr : videoRAM) {
        if(vr) vr->initialize(&dataBus, &addrBus, &rwLine);
    }
}
