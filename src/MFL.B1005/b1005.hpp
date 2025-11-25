#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

template <uint8_t addrOffset>
class B1005 : public signaledDevice {
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[32];
    void            signal() override;
    explicit B1005(B2100 &a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
void B1005<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 11) {
        maskedAddr &= 0x1f;
    }
    signalDevices[maskedAddr]->signal();
}
