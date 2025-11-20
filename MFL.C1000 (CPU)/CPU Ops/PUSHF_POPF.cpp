#include "..\cpu.hpp"

void CPU::PUSHF() {
    pushByte(f);
}

void CPU::POPF() {
    f = popByte();
}
