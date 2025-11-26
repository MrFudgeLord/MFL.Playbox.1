#pragma once

#include <cstdint>

#include "..\device.hpp"
#include "..\scheduledDevice.hpp"
#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"

template <uint8_t addrOffset>
class M1500 : public scheduledDevice, public signaledDevice {
    B2000 &dataBus;
    B2100 &addrBus;
public:
    signaledDevice *signalDevices[32];
    void            signal() override;
    explicit M1500(B2000 &d, B2100 &a)
        : dataBus(d), addrBus(a) {};
};

template <uint8_t addrOffset>
void M1500<addrOffset>::signal() {
    uint16_t maskedAddr = addrBus.val >> addrOffset;
    if constexpr(addrOffset < 11) {
        maskedAddr &= 0x1f;
    }
    signalDevices[maskedAddr]->signal();
}
