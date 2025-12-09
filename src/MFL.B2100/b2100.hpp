#pragma once

#include <cstdint>

#include "..\device.hpp"

class B2100 : public device {
public:
    volatile uint16_t val;
};
