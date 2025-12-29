#pragma once

#include <queue>
#include <cassert>

#include "../basicDeviceClasses/processor.hpp"
#include "../basicDeviceClasses/displayProcessor.hpp"
#include "../basicDeviceClasses/inputDevice.hpp"
#include "../basicDeviceClasses/scheduledDevice.hpp"

// #define DET_SEQ

namespace scheduler {

extern uint64_t    mainClock;
extern uint64_t    nextEventClock;
constexpr uint64_t TICKS_PER_FRAME  = 16'977'600;
constexpr uint64_t TICKS_PER_SECOND = 1'018'656'000; // basically our base clock speed in a way? it's close to but not exactly 1 GHz: 2^6*3^4*5^2*131*60

struct event {
    uint64_t timeSeq;
    uint8_t  deviceIndex;
    uint8_t  callbackIndex;
    uint8_t  data[4];
    uint8_t  reserved[2];
};

extern std::priority_queue<event> eventQueue;

bool operator<(event, event);
void scheduleEvent(event e);
bool handleNextEvent();

void registerProcessor(processor *p);

void registerDisplayProcessor(displayProcessor *dp);

void registerInputDevice(inputDevice *id);

uint8_t registerDevice(scheduledDevice *device);

} // namespace scheduler
