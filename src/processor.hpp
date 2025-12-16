#pragma once

#include "device.hpp"

#include <cstdint>

class processor {
public:
    static inline uint32_t nextEventClock = 0;
    uint32_t               clock;
    virtual void           addCyclePreemptable() = 0;
    virtual void           run()                 = 0;
};
