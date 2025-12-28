#include "../c1000.hpp"

void C1000::SETI() {
    f |= flags::IF;
    addCyclePreemptable();
}

void C1000::CLRI() {
    f &= ~flags::IF;
    addCyclePreemptable();
}

void C1000::SETC() {
    f |= flags::CF;
    addCyclePreemptable();
}

void C1000::CLRC() {
    f &= ~flags::CF;
    addCyclePreemptable();
}
