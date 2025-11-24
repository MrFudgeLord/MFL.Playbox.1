#pragma once

#include "device.hpp"

class signaledDevice : public device {
public:
    virtual void signal();
};
