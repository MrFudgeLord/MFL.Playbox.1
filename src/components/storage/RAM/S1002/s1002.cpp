#include <cstdlib>

#include "s1002.hpp"

bool S1002::initialize(B2000 *d, B2100 *a, B2310 *crw) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
#ifdef MEM_RAND
    for(int i = 0; i < MEM_SIZE / 4; i++) {
        ((uint32_t *) memory)[i] = rand();
    }
#endif
    return true;
}

uint64_t S1002::signal() {
    if(rw->val) {
        memory[addrBus->val & (MEM_SIZE - 1)] = dataBus->val;
    } else {
        dataBus->val = memory[addrBus->val & (MEM_SIZE - 1)];
    }
    return 2 * 2 * 2 * 3 * 5; // 120
}

B3100::info S1002::getInfo() {
    return {memory, MEM_SIZE};
}
