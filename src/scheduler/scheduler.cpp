#include "scheduler.hpp"

namespace scheduler {

bool operator<(event lhs, event rhs) {
#ifdef DET_SEQ
    assert(lhs.timeSeq != rhs.timeSeq);
#endif
    return lhs.timeSeq > rhs.timeSeq;
}

uint8_t registerProcessor(processor *p) {
    processors[processorCount] = p;
    return processorCount++;
}

uint8_t registerCallback(scheduledDevice *device, void (scheduledDevice::*callback)()) {
    static uint8_t nextIndex = 0;
    assert(nextIndex < 255);
    devices[nextIndex]         = device;
    deviceCallbacks[nextIndex] = callback;
    return nextIndex++;
}

void scheduleEvent(event e) {
#ifdef DET_SEQ
    static uint8_t seq   = 0;
    e.timeSeq          <<= 8;
    if((eventQueue.top().timeSeq & 0xffff'ff00) == (e.timeSeq)) {
        seq = eventQueue.top().timeSeq;
        assert(seq < 255);
        seq++;
        e.timeSeq |= seq;
    }
#endif
    eventQueue.push(e);
}

void tick() {
    event nextEvent           = eventQueue.top();
    processor::nextEventClock = nextEvent.timeSeq;
    for(int i = 0; i < processorCount; i++) {
        processors[i]->run();
    }
    scheduledDevice *eventDevice                         = devices[nextEvent.callbackIndex];
    void             (scheduledDevice::*eventCallback)() = deviceCallbacks[nextEvent.callbackIndex];
    (eventDevice->*eventCallback)();
}

} // namespace scheduler
