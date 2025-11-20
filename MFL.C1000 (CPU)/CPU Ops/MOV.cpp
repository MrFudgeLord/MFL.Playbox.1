#include "..\cpu.hpp"

void CPU::MOV_a_b() {
    a = b;
    addCyclePreemptable();
}

void CPU::MOV_a_iB() {
    a = fetchImmByte();
}

void CPU::MOV_a_dB() {
    uint16_t addr = fetchImmWord();
    readMemoryByte(addr, a);
}

void CPU::MOV_a_zpdB() {
    uint16_t addr = fetchImmByte();
    readMemoryByte(addr, a);
}

void CPU::MOV_a_zpxB() {
    uint16_t addr = x;
    readMemoryByte(addr, a);
}

void CPU::MOV_a_zpyB() {
    uint16_t addr = y;
    readMemoryByte(addr, a);
}

void CPU::MOV_a_zpzB() {
    uint16_t addr = z;
    readMemoryByte(addr, a);
}

void CPU::MOV_a_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + x;
    addCyclePreemptable();
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + y;
    addCyclePreemptable();
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + z;
    addCyclePreemptable();
    readMemoryByte(effAddr, a);
}

void CPU::MOV_a_x() {
    a = x;
    addCyclePreemptable();
}

void CPU::MOV_a_y() {
    a = y;
    addCyclePreemptable();
}

void CPU::MOV_a_z() {
    a = z;
    addCyclePreemptable();
}

void CPU::MOV_b_a() {
    b = a;
    addCyclePreemptable();
}

void CPU::MOV_b_iB() {
    b = fetchImmByte();
}

void CPU::MOV_b_dB() {
    uint16_t addr = fetchImmWord();
    readMemoryByte(addr, b);
}

void CPU::MOV_b_zpdB() {
    uint16_t addr = fetchImmByte();
    readMemoryByte(addr, b);
}

void CPU::MOV_b_zpxB() {
    uint16_t addr = x;
    readMemoryByte(addr, b);
}

void CPU::MOV_b_zpyB() {
    uint16_t addr = y;
    readMemoryByte(addr, b);
}

void CPU::MOV_b_zpzB() {
    uint16_t addr = z;
    readMemoryByte(addr, b);
}

void CPU::MOV_b_izpxB() {
    uint16_t addr = x;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_izpyB() {
    uint16_t addr = y;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_izpzB() {
    uint16_t addr = z;
    uint16_t effAddr;
    readMemoryWord(addr, effAddr);
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_dxB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + x;
    addCyclePreemptable();
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_dyB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + y;
    addCyclePreemptable();
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_dzB() {
    uint16_t addr    = fetchImmWord();
    uint16_t effAddr = addr + z;
    addCyclePreemptable();
    readMemoryByte(effAddr, b);
}

void CPU::MOV_b_x() {
    b = x;
    addCyclePreemptable();
}

void CPU::MOV_b_y() {
    b = y;
    addCyclePreemptable();
}

void CPU::MOV_b_z() {
    b = z;
    addCyclePreemptable();
}

void CPU::MOV_x_a() {
    x = a;
    addCyclePreemptable();
}

void CPU::MOV_y_a() {
    y = a;
    addCyclePreemptable();
}

void CPU::MOV_z_a() {
    z = a;
    addCyclePreemptable();
}

void CPU::MOV_x_b() {
    x = b;
    addCyclePreemptable();
}

void CPU::MOV_y_b() {
    y = b;
    addCyclePreemptable();
}

void CPU::MOV_z_b() {
    z = b;
    addCyclePreemptable();
}
