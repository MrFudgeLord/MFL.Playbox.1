#pragma once

#include <cstdint>
#include "scheduledDevice.hpp"

class displayProcessor : public scheduledDevice {
public:
    uint32_t *frameBuffer;
};
