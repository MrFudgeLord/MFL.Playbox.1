#include <cstdlib>

#include "s1102.hpp"

bool S1102::initialize(B2000 *d, B2100 *a, B2310 *crw, B2310 *cl) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
    lock    = cl;
#ifdef MEM_RAND
    for(int i = 0; i < MEM_SIZE / 4; i++) {
        ((uint32_t *) memory)[i] = rand();
    }
#endif
    return true;
}

uint64_t S1102::signal() {
    if(rw->val) {
        if(!lock) memory[addrBus->val & (MEM_SIZE - 1)] = dataBus->val;
    } else {
        dataBus->val = memory[addrBus->val & (MEM_SIZE - 1)];
    }
    return 2 * 2 * 2 * 3 * 5; // 120
}

B3110::info S1102::getInfo() {
    return {memory, MEM_SIZE};
}
