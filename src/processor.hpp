#pragma once

#include "device.hpp"

#include <cstdint>

class processor {
public:
    static uint32_t nextEventClock;
    uint32_t        clock;
    void            addCyclePreemptable();
    virtual void    run();
};
