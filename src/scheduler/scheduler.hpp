#pragma once

#include <functional>
#include <queue>
#include <cassert>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"

// #define DET_SEQ

namespace scheduler {

extern uint32_t mainClock;

struct event {
    uint32_t deviceIndex   : 5;
    uint32_t callbackIndex : 3;
    uint32_t timeSeq       : 24;
    uint8_t  data[4];
};

bool operator<(event, event);
void scheduleEvent(event e);
bool tick();

uint8_t registerProcessor(processor *p);

uint8_t registerDevice(scheduledDevice *device);

} // namespace scheduler
