#include "cpu.hpp"

uint8_t CPU::fetchImmByte() {
    uint8_t val;
    readMemoryByte(i.p, val);
    i.p += 1;
    return val;
}

uint16_t CPU::fetchImmWord() {
    uint16_t val;
    readMemoryWord(i.p, val);
    i.p += 2;
    return val;
}

void CPU::pushByte(uint8_t val) {
    writeMemoryByte(s.p, val);
    s.l -= 1;
    addCyclePreemptable();
}

void CPU::pushWord(uint16_t val) {
    writeMemoryWord(s.p, val);
    s.l -= 2;
    addCyclePreemptable();
}

uint8_t CPU::popByte() {
    s.l += 1;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

uint16_t CPU::popWord() {
    s.l += 2;
    addCyclePreemptable();
    uint8_t val;
    readMemoryByte(s.p, val);
    return val;
}

void CPU::FDE() {
    uint8_t opcode = fetchImmByte();
    (this->*opTable[opcode])();
    if(!rst) {
        reset();
    }
    if(!nmi) {
        nmiInterrupt();
    }
    if(f & IF) {
        if(!irq) irqInterrupt();
    }
}

void CPU::reset() {
    readMemoryWord(0xFFFE, i.p);
    s.p = 0x01FF;
    a   = 0;
    b   = 0;
    x   = 0;
    y   = 0;
    z   = 0;
    f   = 0b10000000;
}

void CPU::nmiInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFC, i.p);
    nmi = false;
}

void CPU::irqInterrupt() {
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFFA, i.p);
    irq = false;
}
