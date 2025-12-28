#pragma once

#include "../signaledDevice.hpp"
#include "../MFL.B2000/b2000.hpp"
#include "../MFL.B2100/b2100.hpp"
#include "../MFL.B2310/b2310.hpp"

// Memory/storage chip socket conforming to the following characteristics:
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
// * 1-bit lock control line

class B3110 : public signaledDevice {
protected:
    B2000 *dataBus;
    B2100 *addrBus;
    B2310 *rw;
    B2310 *lock;
public:
    struct info {
        uint8_t *memory;
        uint32_t size;
    };
public:
    virtual bool initialize(B2000 *d, B2100 *a, B2310 *crw, B2310 *cl) = 0;
    virtual info getInfo()                                             = 0;
};
