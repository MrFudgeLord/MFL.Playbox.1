#pragma once

#include <functional>
#include <queue>
#include <cassert>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"

// #define DET_SEQ

namespace scheduler {

struct event {
    uint32_t timeSeq;
    uint8_t  callbackIndex;
    uint8_t  data[3];
};

bool                       operator<(event, event);
std::priority_queue<event> eventQueue;
void                       scheduleEvent(event e);
void                       tick();

uint8_t    processorCount = 0;
processor *processors[16];
uint8_t    registerProcessor(processor *p);

scheduledDevice *devices[256];
void             (scheduledDevice::*deviceCallbacks[256])();
uint8_t          registerCallback(scheduledDevice *device, void (scheduledDevice::*callback)());

} // namespace scheduler
