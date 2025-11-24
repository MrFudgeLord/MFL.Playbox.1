#include "..\c1000.hpp"

void C1000::SSPH_iB() {
    uint8_t imm = fetchImmByte();
    s.h         = imm;
    addCyclePreemptable();
}

void C1000::SLX() {
    s.l = x;
    addCyclePreemptable();
}

void C1000::XSL() {
    x = s.l;
    addCyclePreemptable();
}
