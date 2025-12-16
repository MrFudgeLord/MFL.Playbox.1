#include "scheduler.hpp"

namespace scheduler {

// CPU clock: 1,697,760 (2^2 * 3^3 * 262 * 60)
//      Per frame: 28,296
// If every CPU cycle completes in 5 cycles (we can average it out to that), at host 5 GHz that's 0.2 ns/cycle, so 1 ns per guest cycle
// At CPU clock speed that's 28,296 ns of CPU time per frame, or ~28.3 us
// One frame is nominally 16.667 ms, or 16,667 us (or 16,666,667 ns!), leaving 16,638,371 ns for everything else per frame
//
// We need to render 240 scanlines per frame
// If VDP is clocked at 4x CPU (and CPU gets 108 cycles per scanline), then VDP gets 432 cycles per scanline
// 432 * 240 = 103,680 rendering cycles per frame
// So VDP takes about 103.7 us per frame
// On top of CPU, we're left with 16,534,691 ns for everything else

uint32_t mainClock = 0;

std::priority_queue<event> eventQueue;

uint8_t    processorCount = 0;
processor *processors[16];

uint8_t          deviceCount = 0;
scheduledDevice *devices[32];

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
    return true;
}

} // namespace scheduler
