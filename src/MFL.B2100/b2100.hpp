#pragma once

#include <cstdint>

#include "..\device.hpp"

// 16-bit system bus

class B2100 : public device {
public:
    volatile uint16_t val;
};
