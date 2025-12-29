#pragma once

#include <cstdint>

#include "../../sockets/peripherals/B3800/b3800.hpp"
#include "../../../scheduler/scheduler.hpp"
#include "../../../basicDeviceClasses/inputDevice.hpp"

class alignas(64) P1000 : public B3800, public inputDevice {
public:
    uint8_t buttonState;
    uint8_t shiftBits;
public:
    uint64_t signal() override;
    bool     initialize(B2000 *d, B2100 *a, B2310 *crw) override;
    void     handleKeyboard(keyboardEvent event) override;
    void     handleMouseMove(mouseMoveEvent event) override;
    void     handleMouseClick(mouseClickEvent event) override;
    void     handleMouseScroll(mouseScrollEvent event) override;
    void     resetInput() override;
};
