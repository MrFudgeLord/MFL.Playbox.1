#pragma once

#include <functional>
#include <queue>
#include <cassert>

#include "..\processor.hpp"
#include "..\scheduledDevice.hpp"

// #define DET_SEQ

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
