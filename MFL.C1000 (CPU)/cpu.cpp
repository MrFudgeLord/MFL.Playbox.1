#include "cpu.hpp"

uint8_t CPU::fetchImmByte() {
    uint8_t val;
    readMemoryByte(ip + insSize, val);
    insSize++;
    return val;
}

uint16_t CPU::fetchImmWord() {
    uint16_t val;
    readMemoryWord(ip + insSize, val);
    insSize += 2;
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
