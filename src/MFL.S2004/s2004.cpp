#include <cstdlib>

#include "s2004.hpp"

bool S2004::initialize(B2000 *d, B2100 *a, B2310 *crw) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
    return true;
}

uint64_t S2004::signal() {
    dataBus->val = memory[addrBus->val & (MEM_SIZE - 1)];
    return 2 * 3 * 5 * 5; // 150
}

B3100::info S2004::getInfo() {
    return {memory, MEM_SIZE};
}
