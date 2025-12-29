#pragma once

#include "../../../../basicDeviceClasses/signaledDevice.hpp"
#include "../../../busses/B2000/b2000.hpp"
#include "../../../busses/B2100/b2100.hpp"
#include "../../../busses/B2310/b2310.hpp"

// Motherboard connection port conforming to the following characteristics:
//
// * is a signaledDevice
//
// * any signal handler
//
// * 8-bit data bus
//
// * 16-bit address bus
//
// * 1-bit read/write control line
//
// * 1-bit non-maskable interrupt line
//
// * 1-bit interrupt request line
//
// * 1-bit reset line

class B3900 : public signaledDevice {
protected:
    signaledDevice *signalHandler;
    B2000          *dataBus;
    B2100          *addrBus;
    B2310          *rw;
    B2310          *nmi;
    B2310          *irq;
    B2310          *rst;
public:
    virtual bool initialize(signaledDevice *sh, B2000 *d, B2100 *a, B2310 *crw, B2310 *cnmi, B2310 *cirq) = 0;
};
