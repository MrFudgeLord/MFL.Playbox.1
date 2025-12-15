#include "c1000.hpp"

void C1000::readMemoryByte(uint16_t addr, uint8_t &dest) {
    rw->val      = false;
    addrBus->val = addr;
    signalHandler->signal();
    dest = dataBus->val;
    addCyclePreemptable();
}

void C1000::readMemoryWord(uint16_t addr, uint16_t &dest) {
    rw->val      = false;
    addrBus->val = addr + 1;
    signalHandler->signal();
    dest = dataBus->val;
    addCyclePreemptable();
    rw->val      = false;
    addrBus->val = addr;
    signalHandler->signal();
    dest = dataBus->val;
}

void C1000::writeMemoryByte(uint16_t addr, uint8_t &src) {
    rw->val      = true;
    addrBus->val = addr;
    dataBus->val = src;
    signalHandler->signal();
    addCyclePreemptable();
}

void C1000::writeMemoryWord(uint16_t addr, uint16_t &src) {
    rw->val      = true;
    addrBus->val = addr;
    dataBus->val = (uint8_t) src;
    signalHandler->signal();
    addCyclePreemptable();
    rw->val      = true;
    addrBus->val = addr + 1;
    dataBus->val = src >> 8;
    signalHandler->signal();
    addCyclePreemptable();
}

uint8_t C1000::fetchImmByte() {
    uint8_t val;
    readMemoryByte(i.p, val);
    i.p += 1;
    return val;
}

uint16_t C1000::fetchImmWord() {
    uint16_t val;
    readMemoryWord(i.p, val);
    i.p += 2;
    return val;
}

void C1000::pushByte(uint8_t val) {
    writeMemoryByte(s.p, val);
    s.l -= 1;
    addCyclePreemptable();
}

void C1000::pushWord(uint16_t val) {
    writeMemoryWord(s.p, val);
    s.l -= 2;
    addCyclePreemptable();
}

uint8_t C1000::popByte() {
    s.l += 1;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

uint16_t C1000::popWord() {
    s.l += 2;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

void C1000::FDE() {
    if(!rst->val) {
        reset();
    }
    if(!nmi->val) {
        nmiInterrupt();
    }
    if(f & IF) {
        if(!irq->val) irqInterrupt();
    }
    uint8_t opcode = fetchImmByte();
    (this->*opTable[opcode])();
}

void C1000::reset() {
    readMemoryWord(0xFFFE, i.p);
    s.h = 0x01;
    addCyclePreemptable();
    s.l = 0xff;
    addCyclePreemptable();
    a = 0;
    addCyclePreemptable();
    b = 0;
    addCyclePreemptable();
    x = 0;
    addCyclePreemptable();
    y = 0;
    addCyclePreemptable();
    z = 0;
    addCyclePreemptable();
    f = IF;
    addCyclePreemptable();
    nmi->val = false;
    irq->val = false;
    rst->val = false;
}

void C1000::nmiInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFC, i.p);
    nmi->val = false;
}

void C1000::irqInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFA, i.p);
    irq->val = false;
}
