#pragma once

#include <cstdint>

#include "../MFL.B3110/b3110.hpp"

// 1024x8 Lockable Random-Access Memory
//
// Memory is member

class alignas(64) S1103 : public B3110 {
public:
    const static uint32_t MEM_SIZE = 1 << 10;
    uint8_t               memory[MEM_SIZE];
    uint64_t              signal() override;
    bool                  initialize(B2000 *d, B2100 *a, B2310 *crw, B2310 *cl) override;
    info                  getInfo() override;
};
