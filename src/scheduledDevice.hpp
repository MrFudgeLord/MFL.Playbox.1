#pragma once

#include <cstdint>

#include "device.hpp"

class scheduledDevice : public device {
public:
    uint8_t          deviceID;
    virtual uint32_t dispatchEvent(uint8_t index, uint8_t data[4]) = 0;
};
