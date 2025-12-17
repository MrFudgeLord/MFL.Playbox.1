#pragma once

#include <cstdint>

class processor {
public:
    // keeps track of every cycle ever run
    uint64_t longClock = 0;
    // set to mainClock after each event, meaning it resets every frame
    uint32_t     eventClock            = 0;
    virtual void addCyclePreemptable() = 0;
    virtual void run()                 = 0;
};
