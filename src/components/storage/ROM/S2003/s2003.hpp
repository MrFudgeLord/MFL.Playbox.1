#pragma once

#include <cstdint>

#include "../../../sockets/storage/B3100/b3100.hpp"

// 8192x8 Read-only Memory
//
// Memory is member

class alignas(64) S2003 : public B3100 {
public:
    const static uint32_t MEM_SIZE = 1 << 10;
    uint8_t               memory[MEM_SIZE];
    uint64_t              signal() override;
    bool                  initialize(B2000 *d, B2100 *a, B2310 *crw) override;
    info                  getInfo() override;
};
