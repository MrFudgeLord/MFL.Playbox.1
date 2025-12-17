#pragma once

#include <cstdint>

#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"

// 3-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1003 : public signaledDevice {
public:
    B2100 *addrBus;
public:
    signaledDevice *signalDevices[8];
    uint32_t        signal() override;
    B1003(B2100 *a)
        : addrBus(a) {};
};

template <uint8_t addrOffset>
uint32_t B1003<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus->val >> addrOffset;
    // printf("\nB1003: Decoding address %04X with offset %d\n", addrBus->val, addrOffset);
    if constexpr(addrOffset < 13) {
        maskedAddr &= 0x03;
    }
    // printf("B1003: Masked address %04X\n", maskedAddr);
    // printf("B1003: signalDevices[maskedAddr] = %p\n", signalDevices[maskedAddr]);
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}
