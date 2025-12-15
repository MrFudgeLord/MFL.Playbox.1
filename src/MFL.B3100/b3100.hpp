#pragma once

#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"

class B3100 : public signaledDevice {
protected:
    B2000 *dataBus;
    B2100 *addrBus;
    B2310 *rw;
public:
    virtual bool initialize(B2000 *d, B2100 *a, B2310 *crw);
};
