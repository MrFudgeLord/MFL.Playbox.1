#include "scheduler.hpp"

namespace scheduler {

// CPU clock: 1,697,760 (2^2 * 3^3 * 262 * 60)
//      Per frame: 28,296
// If every CPU cycle completes in 5 cycles (we can average it out to that), at host 5 GHz that's 0.2 ns/cycle, so 1 ns per guest cycle
// At CPU clock speed that's 28,296 ns of CPU time per frame, or ~28.3 us
// One frame is nominally 16.667 ms, or 16,667 us (or 16,666,667 ns!), leaving 16,638,371 ns for everything else per frame

uint32_t mainClock      = 0;
uint32_t nextEventClock = CLOCKS_PER_FRAME;

std::priority_queue<event> frameEventQueue;
std::priority_queue<event> futureEventQueue;

processor *processorPtr = nullptr;

displayProcessor *displayProcessorPtr = nullptr;

inputDevice *inputDevicePtr = nullptr;

uint8_t          deviceCount = 1;
scheduledDevice *devices[32];

bool operator<(event lhs, event rhs) {
#ifdef DET_SEQ
    assert(lhs.timeSeq != rhs.timeSeq);
#endif
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
    assert(deviceCount < 32);
    devices[deviceCount] = device;
    return deviceCount++;
}

void scheduleEvent(event e) {
#ifdef DET_SEQ
    static uint8_t seq   = 0;
    e.timeSeq          <<= 4;
    if((eventQueue.top().timeSeq & 0xff'fff0) == (e.timeSeq)) {
        seq = eventQueue.top().timeSeq;
        assert(seq < 16);
        seq++;
        e.timeSeq |= seq;
    }
#endif
    if(e.timeSeq < CLOCKS_PER_FRAME) [[likely]] {
        frameEventQueue.push(e);
    } else {
        futureEventQueue.push(e);
    }
    if(e.timeSeq < nextEventClock) {
        nextEventClock = e.timeSeq;
    }
}

bool handleNextEvent() {
    event nextEvent = frameEventQueue.top();
    frameEventQueue.pop();
    // printf("\nEvent: {%i, %i, %i, 0x%08X}\n", nextEvent.deviceIndex, nextEvent.callbackIndex, nextEvent.timeSeq, *(uint32_t *) nextEvent.data);
    devices[nextEvent.deviceIndex]->dispatchEvent(nextEvent.callbackIndex, nextEvent.data);
    nextEventClock = frameEventQueue.top().timeSeq;
    return true;
}

} // namespace scheduler
