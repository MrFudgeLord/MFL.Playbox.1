#include "s1000.hpp"
#include <cstdlib>
#include <ctime>

void S1000::initMemory() {
    srand(time(0));
    for(int i = 0; i < MEM_SIZE / 4; i++) {
        ((uint32_t *) memory)[i] = rand();
    }
}

void S1000::signal() {
    if(controlBus.val) {
        memory[addrBus.val & 0x3ff] = dataBus.val;
    } else {
        dataBus.val = memory[addrBus.val & 0x3ff];
    }
}
