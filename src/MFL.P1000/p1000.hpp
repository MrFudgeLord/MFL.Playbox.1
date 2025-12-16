#pragma once

#include <cstdint>

#include "..\MFL.B3800\b3800.hpp"

class alignas(64) P1000 : public B3800 {
public:
    uint32_t signal() override;
    bool     initialize(B2000 *d, B2100 *a, B2310 *crw) override;
};
