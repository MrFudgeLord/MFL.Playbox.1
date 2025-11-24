#include "..\c1000.hpp"

void C1000::PUSHF() {
    f &= 0b11110001;
    pushByte(f);
}

void C1000::POPF() {
    f  = popByte();
    f &= 0b11110001;
}
