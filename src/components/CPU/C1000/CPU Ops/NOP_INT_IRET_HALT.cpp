#include "../c1000.hpp"

void C1000::NOP() {
    return;
}

void C1000::INT() {
    // RST FFFE:FFFF
    // NMI FFFC:FFFD
    // IRQ FFFA:FFFB
    // INT FFF8:FFF9
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFF8, i.p);
}

void C1000::IRET() {
    f   = popByte();
    i.p = popWord();
}

void C1000::HALT() {
    printState();
    while(!(irq->val || nmi->val || rst->val)) {
        addCyclePreemptable();
    }
    printState();
}
