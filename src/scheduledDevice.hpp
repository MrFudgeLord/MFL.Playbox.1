#pragma once

#include <cstdint>

#include "device.hpp"

class scheduledDevice : public device {
public:
    uint8_t      deviceID;
    virtual bool dispatchEvent(uint8_t index, uint8_t data[4]); // return true if blocking?
};
