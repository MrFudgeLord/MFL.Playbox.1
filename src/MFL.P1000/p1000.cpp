#include "p1000.hpp"

bool P1000::initialize(B2000 *d, B2100 *a) {
    dataBus = d;
    addrBus = a;
    scheduler::registerInputDevice(this);
    return true;
}

uint32_t P1000::signal() {
    dataBus->val = buttonState;
    return 8;
}

void P1000::handleKeyboard(keyboardEvent event) {
    enum keybinds {
        dpadUp       = SDLK_W,
        dpadDown     = SDLK_S,
        dpadLeft     = SDLK_A,
        dpadRight    = SDLK_D,
        buttonA      = SDLK_J,
        buttonB      = SDLK_L,
        buttonStart  = SDLK_LEFTBRACKET,
        buttonSelect = SDLK_RIGHTBRACKET
    };
    switch(event.keycode) {
        case dpadUp:
            buttonState |= 0b10000000;
            break;
        case dpadDown:
            buttonState |= 0b01000000;
            break;
        case dpadLeft:
            buttonState |= 0b00100000;
            break;
        case dpadRight:
            buttonState |= 0b00010000;
            break;
        case buttonA:
            buttonState |= 0b00001000;
            break;
        case buttonB:
            buttonState |= 0b00000100;
            break;
        case buttonStart:
            buttonState |= 0b00000010;
            break;
        case buttonSelect:
            buttonState |= 0b00000001;
            break;
    }
}

void P1000::handleMouseMove(mouseMoveEvent event) {
    return;
}

void P1000::handleMouseClick(mouseClickEvent event) {
    return;
}

void P1000::handleMouseScroll(mouseScrollEvent event) {
    return;
}

void P1000::resetInput() {
    buttonState = 0;
}
