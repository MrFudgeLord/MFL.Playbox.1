#pragma once

#include <cstdint>

#include "device.hpp"

class scheduledDevice : public device {
public:
    virtual void dispatchEvent(uint8_t index, uint8_t data[4]);
};
