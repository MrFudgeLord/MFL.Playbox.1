#include "..\cpu.hpp"

void CPU::POP_a() {
    a = popByte();
}

void CPU::POP_b() {
    b = popByte();
}

void CPU::POP_x() {
    x = popByte();
}

void CPU::POP_y() {
    y = popByte();
}

void CPU::POP_z() {
    z = popByte();
}
