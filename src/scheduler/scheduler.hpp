#pragma once

#include <functional>
#include <queue>
#include <cassert>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"

// #define DET_SEQ

namespace scheduler {

// CPU clock: 1,697,760 (2^3 * 3^3 * 131 * 60)
//

uint32_t mainClock = 0;

struct event {
    uint32_t deviceIndex   : 5;
    uint32_t callbackIndex : 3;
    uint32_t timeSeq       : 24;
    uint8_t  data[4];
};

bool                       operator<(event, event);
std::priority_queue<event> eventQueue;
void                       scheduleEvent(event e);
void                       tick();

uint8_t    processorCount = 0;
processor *processors[16];
uint8_t    registerProcessor(processor *p);

uint8_t          deviceCount = 0;
scheduledDevice *devices[32];
uint8_t          registerDevice(scheduledDevice *device);

} // namespace scheduler

class frameEndDummy : public scheduledDevice {
    uint8_t deviceNumber;
    void    dispatchEvent(uint8_t index, uint8_t data[4]) override;
    frameEndDummy() : deviceNumber(scheduler::registerDevice(this)) {};
};
