#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

template <uint8_t addrOffset>
class B1002 : public signaledDevice {
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[4];
    void            signal() override;
    B1002(B2100 &a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
void B1002<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 14) {
        maskedAddr &= 0x07;
    }
    if(signalDevices[maskedAddr]) signalDevices[maskedAddr]->signal();
}
