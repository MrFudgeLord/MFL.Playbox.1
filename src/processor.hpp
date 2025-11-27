#pragma once

#include "device.hpp"

#include <cstdint>

class processor : public device {
public:
    static uint32_t nextEventClock;
    virtual void    run();
    void            addCyclePreemptable();
};
