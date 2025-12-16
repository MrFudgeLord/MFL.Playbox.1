#pragma once

#include <cstdint>

#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"

class alignas(64) S2000 : public signaledDevice {
    B2000 &dataBus;
    B2100 &addrBus;
public:
    const static uint32_t MEM_SIZE = 1 << 12;
    uint8_t               memory[MEM_SIZE];
    void                  initMemory();
    uint32_t              signal() override;
    explicit S2000(B2000 &d, B2100 &a)
        : dataBus(d), addrBus(a) {};
};
