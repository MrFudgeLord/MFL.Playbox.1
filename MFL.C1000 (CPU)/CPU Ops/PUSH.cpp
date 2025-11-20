#include "..\cpu.hpp"

void CPU::PUSH_a() {
    pushByte(a);
}

void CPU::PUSH_b() {
    pushByte(b);
}

void CPU::PUSH_x() {
    pushByte(x);
}

void CPU::PUSH_y() {
    pushByte(y);
}

void CPU::PUSH_z() {
    pushByte(z);
}
