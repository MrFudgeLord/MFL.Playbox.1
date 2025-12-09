#include "scheduler.hpp"

namespace scheduler {

bool operator<(event lhs, event rhs) {
#ifdef DET_SEQ
    assert(lhs.timeSeq != rhs.timeSeq);
#endif
    return lhs.timeSeq > rhs.timeSeq;
}

uint8_t registerProcessor(processor *p) {
    assert(processorCount < 16);
    processors[processorCount] = p;
    return processorCount++;
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
    eventQueue.push(e);
}

bool tick() {
    event nextEvent           = eventQueue.top();
    processor::nextEventClock = nextEvent.timeSeq;
    for(int i = 0; i < processorCount; i++) {
        processors[i]->run();
    }
    devices[nextEvent.deviceIndex]->dispatchEvent(nextEvent.callbackIndex, nextEvent.data);
}

} // namespace scheduler

void frameEndDummy::dispatchEvent(uint8_t index, uint8_t data[4]) {
    using namespace scheduler;
    mainClock = 0;
    scheduleEvent({.deviceIndex = deviceNumber, .timeSeq = 28'296});
}
