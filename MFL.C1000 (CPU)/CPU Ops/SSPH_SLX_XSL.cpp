#include "..\cpu.hpp"

void CPU::SSPH_iB() {
    uint8_t imm = fetchImmByte();
    s.h         = imm;
    addCyclePreemptable();
}

void CPU::SLX() {
    s.l = x;
    addCyclePreemptable();
}

void CPU::XSL() {
    x = s.l;
    addCyclePreemptable();
}
