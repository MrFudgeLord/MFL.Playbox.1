#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

// Number X such that the lowest bit of the portion of the address bus which is decoded, is bit X of the address bus.
// Ex: addrOffset = 12 -> lowest bit of decoding is address bus bit 12, so it decodes bits 12:15
template <uint8_t addrOffset>
class B1004 : public signaledDevice {
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[16];
    void            signal() override;
    explicit B1004(B2100 &a) : addrBus(a) {};
};

template <uint8_t addrOffset>
void B1004<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 12) {
        maskedAddr &= 0x0f;
    }
    signalDevices[maskedAddr]->signal();
}
