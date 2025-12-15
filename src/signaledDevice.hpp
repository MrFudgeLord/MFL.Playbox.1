#pragma once

#include "device.hpp"

#include <cstdint>

class signaledDevice : public device {
public:
    virtual uint32_t signal(); // return number of cycles taken
};
