#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

// 4-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1004 : public signaledDevice {
public:
    B2100 *addrBus;
public:
    signaledDevice *signalDevices[16];
    uint32_t        signal() override;
    explicit B1004(B2100 *a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
uint32_t B1004<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus->val >> addrOffset;
    // printf("B1004: Decoding address %04X with offset %d\n", addrBus->val, addrOffset);
    if constexpr(addrOffset < 12) {
        maskedAddr &= 0x0f;
    }
    // printf("B1004: Masked address %04X\n", maskedAddr);
    // printf("B1004: signalDevices[maskedAddr] = %p\n", signalDevices[maskedAddr]);
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}
