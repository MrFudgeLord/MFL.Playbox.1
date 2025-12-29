#pragma once

#include "../../../basicDeviceClasses/signaledDevice.hpp"
#include "../../busses/B2000/b2000.hpp"
#include "../../busses/B2100/b2100.hpp"
#include "../../busses/B2310/b2310.hpp"

// Address-to-signal decoder conforming to the following characteristics:
//
// * is a signaledDevice
//
// * 16-bit address bus

class B3980 : public signaledDevice {
protected:
    B2100 *addrBus;
public:
    virtual bool initialize(B2100 *a) = 0;
};
