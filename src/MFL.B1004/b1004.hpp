#pragma once

#include <cstdint>

#include "../signaledDevice.hpp"
#include "../MFL.B2100/b2100.hpp"
#include "../MFL.B3980/b3980.hpp"

// 4-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1004 : public B3980 {
public:
    signaledDevice *signalDevices[16];
    uint64_t        signal() override;
    bool            initialize(B2100 *a) override;
};

template <uint8_t addrOffset>
uint64_t B1004<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus->val >> addrOffset;
    if constexpr(addrOffset < 12) {
        maskedAddr &= 0x0f;
    }
    // printf("B1004: Decoding address %04X with offset %d on bus %p\n", addrBus->val, addrOffset, addrBus);
    // printf("B1004: Masked address %04X\n", maskedAddr);
    // printf("B1004: signalDevices[maskedAddr] = %p\n", signalDevices[maskedAddr]);
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}

template <uint8_t addrOffset>
bool B1004<addrOffset>::initialize(B2100 *a) {
    addrBus = a;
    return true;
}
