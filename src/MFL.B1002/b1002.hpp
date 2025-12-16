#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

// 2-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1002 : public signaledDevice {
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[4];
    uint32_t        signal() override;
    B1002(B2100 &a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
uint32_t B1002<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 14) {
        maskedAddr &= 0x07;
    }
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}
