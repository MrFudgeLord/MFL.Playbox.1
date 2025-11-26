#pragma once

#include <cstdint>

#include "..\signaledDevice.hpp"
#include "..\MFL.B2000\b2000.hpp"
#include "..\MFL.B2100\b2100.hpp"
#include "..\MFL.B2310\b2310.hpp"

class alignas(64) S1000 : public signaledDevice {
    B2000 &dataBus;
    B2100 &addrBus;
    B2310 &controlBus;
public:
    const static uint32_t MEM_SIZE = 1 << 10;
    uint8_t               memory[MEM_SIZE];
    void                  initMemory();
    void                  signal() override;
    explicit S1000(B2000 &d, B2100 &a, B2310 &c) : dataBus(d), addrBus(a), controlBus(c) {};
};
