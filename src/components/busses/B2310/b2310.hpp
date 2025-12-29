#pragma once

#include "../../../basicDeviceClasses/device.hpp"

// 1-bit system bus

class B2310 : public device {
public:
    volatile bool val;
};
