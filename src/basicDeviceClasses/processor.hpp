#pragma once

#include <cstdint>

class processor {
public:
    const uint64_t ticksPerCycle;
    // tracks ticks
    uint64_t clock = 0;
    // tracks cycles
    uint64_t     cycleClock            = 0;
    virtual void addCyclePreemptable() = 0;
    virtual void run()                 = 0;
    virtual void printState()          = 0;
    processor(uint64_t tpc) : ticksPerCycle(tpc) {};
};
