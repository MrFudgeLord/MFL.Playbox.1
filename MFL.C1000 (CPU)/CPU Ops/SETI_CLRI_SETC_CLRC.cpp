#include "..\cpu.hpp"

void CPU::SETI() {
    f |= IF;
    addCyclePreemptable();
}

void CPU::CLRI() {
    f &= ~IF;
    addCyclePreemptable();
}

void CPU::SETC() {
    f |= CF;
    addCyclePreemptable();
}

void CPU::CLRC() {
    f &= ~CF;
    addCyclePreemptable();
}
