#pragma once

#include "device.hpp"

#include <cstdint>

class signaledDevice : public device {
public:
    virtual uint64_t signal() = 0; // return number of cycles taken
};
