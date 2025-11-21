#include "..\cpu.hpp"

void CPU::NOP() {
    return;
}

void CPU::INT() {
    // RST FFFE:FFFF
    // NMI FFFC:FFFD
    // IRQ FFFA:FFFB
    // INT FFF8:FFF9
    pushWord(i.p);
    pushByte(f);
    readMemoryWord(0xFFF8, i.p);
}

void CPU::IRET() {
    f   = popByte();
    i.p = popWord();
}
