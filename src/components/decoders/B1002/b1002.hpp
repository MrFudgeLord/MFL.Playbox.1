#pragma once

#include <cstdint>

#include "../../../basicDeviceClasses/signaledDevice.hpp"
#include "../../busses/B2100/b2100.hpp"
#include "../../sockets/decoders/B3980/b3980.hpp"

// 2-bit address-to-signal decoder with variable bit offset, is also a signaledDevice to allow for chaining

template <uint8_t addrOffset>
class B1002 : public B3980 {
public:
    signaledDevice *signalDevices[4];
    uint64_t        signal() override;
    bool            initialize(B2100 *a) override;
};

template <uint8_t addrOffset>
uint64_t B1002<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus->val >> addrOffset;
    if constexpr(addrOffset < 14) {
        maskedAddr &= 0x03;
    }
    // printf("B1002: Decoding address %04X with offset %d on bus %p\n", addrBus->val, addrOffset, addrBus);
    // printf("B1002: Masked address %04X\n", maskedAddr);
    // printf("B1002: signalDevices[maskedAddr] = %p\n", signalDevices[maskedAddr]);
    return signalDevices[maskedAddr] ? signalDevices[maskedAddr]->signal() : 1;
}

template <uint8_t addrOffset>
bool B1002<addrOffset>::initialize(B2100 *a) {
    addrBus = a;
    return true;
}
