#pragma once

#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"

class B3800 : public signaledDevice {
protected:
    B2000 *dataBus;
    B2100 *addrBus;
public:
    virtual bool initialize(B2000 *d, B2100 *a);
};
