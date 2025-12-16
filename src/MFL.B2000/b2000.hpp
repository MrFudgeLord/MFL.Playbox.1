#pragma once

#include <cstdint>

#include "..\device.hpp"

// 8-bit system bus

class B2000 : public device {
public:
    volatile uint8_t val;
};
