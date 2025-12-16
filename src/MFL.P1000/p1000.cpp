#include "p1000.hpp"

bool P1000::initialize(B2000 *d, B2100 *a, B2310 *crw) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
    return true;
}

uint32_t P1000::signal() {
    return 0;
}
