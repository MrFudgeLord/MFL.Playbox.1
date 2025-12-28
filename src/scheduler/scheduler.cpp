#include "scheduler.hpp"

namespace scheduler {

// CPU clock: 1,697,760 (2^2 * 3^3 * 262 * 60)
//      Per frame: 28,296
// If every CPU cycle completes in 5 cycles (we can average it out to that), at host 5 GHz that's 0.2 ns/cycle, so 1 ns per guest cycle
// At CPU clock speed that's 28,296 ns of CPU time per frame, or ~28.3 us
// One frame is nominally 16.667 ms, or 16,667 us (or 16,666,667 ns!), leaving 16,638,371 ns for everything else per frame

uint64_t mainClock      = 0;
uint64_t nextEventClock = 0xFFFF'FFFF'FFFF'FFFF;

std::priority_queue<event> eventQueue;

processor *processorPtr = nullptr;

displayProcessor *displayProcessorPtr = nullptr;

inputDevice *inputDevicePtr = nullptr;

scheduledDevice *devices[256];

bool operator<(event lhs, event rhs) {
    return lhs.timeSeq > rhs.timeSeq;
}

void registerProcessor(processor *p) {
    processorPtr = p;
}

void registerDisplayProcessor(displayProcessor *dp) {
    displayProcessorPtr = dp;
}

void registerInputDevice(inputDevice *id) {
    inputDevicePtr = id;
}

uint8_t registerDevice(scheduledDevice *device) {
    static uint8_t deviceCount = 1;
    assert(deviceCount != 0);
    devices[deviceCount] = device;
    return deviceCount++;
}

void scheduleEvent(event e) {
    eventQueue.push(e);
    if(e.timeSeq < nextEventClock) {
        nextEventClock = e.timeSeq;
    }
}

bool handleNextEvent() {
    event nextEvent = eventQueue.top();
    eventQueue.pop();
    // printf("Event: {%lli, %i, %i, 0x%08X}\n", nextEvent.timeSeq, nextEvent.deviceIndex, nextEvent.callbackIndex, *(uint32_t *) nextEvent.data);
    devices[nextEvent.deviceIndex]->dispatchEvent(nextEvent.callbackIndex, nextEvent.data);
    nextEventClock = eventQueue.top().timeSeq;
    return true;
}

} // namespace scheduler
