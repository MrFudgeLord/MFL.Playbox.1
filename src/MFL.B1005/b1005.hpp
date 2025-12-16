#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

// 5-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1005 : public signaledDevice {
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[32];
    uint32_t        signal() override;
    explicit B1005(B2100 &a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
uint32_t B1005<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 11) {
        maskedAddr &= 0x1f;
    }
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}
