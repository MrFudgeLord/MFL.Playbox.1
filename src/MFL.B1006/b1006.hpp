#pragma once

#include <cstdint>

#include "..\signaledDevice.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B3980\b3980.hpp"

// 6-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1006 : public B3980 {
public:
    signaledDevice *signalDevices[64];
    uint32_t        signal() override;
    bool            initialize(B2100 *a) override;
};

template <uint8_t addrOffset>
uint32_t B1006<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus->val >> addrOffset;
    if constexpr(addrOffset < 11) {
        maskedAddr &= 0x3f;
    }
    // printf("B1006: Decoding address %04X with offset %d on bus %p\n", addrBus->val, addrOffset, addrBus);
    // printf("B1006: Masked address %04X\n", maskedAddr);
    // printf("B1006: signalDevices[maskedAddr] = %p\n", signalDevices[maskedAddr]);
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}

template <uint8_t addrOffset>
bool B1006<addrOffset>::initialize(B2100 *a) {
    addrBus = a;
    return true;
}
