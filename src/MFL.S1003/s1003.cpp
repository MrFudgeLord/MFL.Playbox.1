#include <cstdlib>

#include "s1003.hpp"

bool S1003::initialize(B2000 *d, B2100 *a, B2310 *crw) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
    for(int i = 0; i < MEM_SIZE / 4; i++) {
        ((uint32_t *) memory)[i] = rand();
    }
    return true;
}

uint32_t S1003::signal() {
    if(rw->val) {
        memory[addrBus->val & (MEM_SIZE - 1)] = dataBus->val;
    } else {
        dataBus->val = memory[addrBus->val & (MEM_SIZE - 1)];
    }
    return 1;
}

B3100::info S1003::getInfo() {
    return {memory, MEM_SIZE};
}
