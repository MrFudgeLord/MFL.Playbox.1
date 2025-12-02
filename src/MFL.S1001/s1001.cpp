#include "s1001.hpp"
#include <cstdlib>

bool S1001::initialize() {
    for(int i = 0; i < MEM_SIZE / 4; i++) {
        ((uint32_t *) memory)[i] = rand();
    }
    return false;
}

void S1001::signal() {
    if(controlBus.val) {
        memory[addrBus.val & (MEM_SIZE - 1)] = dataBus.val;
    } else {
        dataBus.val = memory[addrBus.val & (MEM_SIZE - 1)];
    }
}
