#include "dummy.hpp"

void dummy::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static void (dummy::*eventHandlers[8])(uint8_t[4]) = {
        &dummy::frameEnd,
        &dummy::debugger,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    (this->*eventHandlers[index])(data);
}
