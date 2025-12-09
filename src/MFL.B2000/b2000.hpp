#pragma once

#include <cstdint>

#include "..\device.hpp"

class B2000 : public device {
public:
    volatile uint8_t val;
};
