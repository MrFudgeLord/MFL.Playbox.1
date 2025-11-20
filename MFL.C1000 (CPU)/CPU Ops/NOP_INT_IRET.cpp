#include "..\cpu.hpp"

void CPU::NOP() {
    addCyclePreemptable();
}

void CPU::INT_iB() {
    uint8_t imm  = fetchImmByte();
    imm         &= 0xF;
    pushByte(f);
    pushWord(ip);
    addCyclePreemptable();
}

void CPU::IRET() {
}
