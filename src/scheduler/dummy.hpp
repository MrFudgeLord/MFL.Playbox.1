#pragma once

#include "..\scheduledDevice.hpp"
#include "..\MFL.M1000\m1000.hpp"

class dummy : public scheduledDevice {
    M1000 *mb;
public:
    dummy(M1000 *mbptr);
    bool dispatchEvent(uint8_t index, uint8_t data[4]) override;
private:
    void frameEnd(uint8_t data[4]);
    void debugger(uint8_t data[4]);
private:
    uint64_t lastFrameEndns;
};
