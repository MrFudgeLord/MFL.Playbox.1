#pragma once

#include <cstdint>

#include "..\MFL.B3800\b3800.hpp"
#include "..\scheduler\scheduler.hpp"
#include "..\inputDevice.hpp"

class alignas(64) P1000 : public B3800, public inputDevice {
public:
    uint8_t buttonState;
public:
    uint32_t signal() override;
    bool     initialize(B2000 *d, B2100 *a) override;
    void     handleKeyboard(keyboardEvent event) override;
    void     handleMouseMove(mouseMoveEvent event) override;
    void     handleMouseClick(mouseClickEvent event) override;
    void     handleMouseScroll(mouseScrollEvent event) override;
    void     resetInput() override;
};
