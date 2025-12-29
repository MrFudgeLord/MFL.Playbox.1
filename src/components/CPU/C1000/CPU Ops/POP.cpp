#include "../c1000.hpp"

void C1000::POP_a() {
    a = popByte();
}

void C1000::POP_b() {
    b = popByte();
}

void C1000::POP_x() {
    x = popByte();
}

void C1000::POP_y() {
    y = popByte();
}

void C1000::POP_z() {
    z = popByte();
}
