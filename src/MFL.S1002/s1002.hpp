#pragma once

#include <cstdint>

#include "..\MFL.B3100\b3100.hpp"

class alignas(64) S1002 : public B3100 {
public:
    const static uint32_t MEM_SIZE = 1 << 9;
    uint8_t               memory[MEM_SIZE];
    uint32_t              signal() override;
    bool                  initialize(B2000 *d, B2100 *a, B2310 *crw) override;
    info                  getInfo() override;
};
