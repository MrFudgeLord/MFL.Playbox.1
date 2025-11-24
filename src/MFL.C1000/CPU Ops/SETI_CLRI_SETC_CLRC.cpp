#include "..\c1000.hpp"

void C1000::SETI() {
    f |= IF;
    addCyclePreemptable();
}

void C1000::CLRI() {
    f &= ~IF;
    addCyclePreemptable();
}

void C1000::SETC() {
    f |= CF;
    addCyclePreemptable();
}

void C1000::CLRC() {
    f &= ~CF;
    addCyclePreemptable();
}
