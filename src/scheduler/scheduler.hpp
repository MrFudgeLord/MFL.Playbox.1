#pragma once

#include <queue>
#include <cassert>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"

// #define DET_SEQ

namespace scheduler {

extern uint32_t    mainClock;
extern uint32_t    nextEventClock;
constexpr uint32_t CLOCKS_PER_FRAME = 28'296;

struct event {
    uint32_t deviceIndex   : 5;
    uint32_t callbackIndex : 3;
    uint32_t timeSeq       : 24;
    uint8_t  data[4];
};

extern std::priority_queue<event> frameEventQueue;
extern std::priority_queue<event> futureEventQueue;

bool operator<(event, event);
void scheduleEvent(event e);
bool handleNextEvent();

uint8_t registerProcessor(processor *p);

uint8_t registerDevice(scheduledDevice *device);

} // namespace scheduler
