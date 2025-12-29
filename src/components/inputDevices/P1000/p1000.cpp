#include "p1000.hpp"

bool P1000::initialize(B2000 *d, B2100 *a, B2310 *crw) {
    dataBus = d;
    addrBus = a;
    rw      = crw;
    scheduler::registerInputDevice(this);
    return true;
}

uint64_t P1000::signal() {
    if(rw->val) {
        shiftBits = buttonState;
    } else {
        shiftBits    >>= 1;
        dataBus->val   = shiftBits & 0x1;
    }
    return 2 * 2 * 5 * 5; // 100
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
    if(event.keyUp) {
        switch(event.keycode) {
            case dpadUp:
                buttonState &= 0b01111111;
                break;
            case dpadDown:
                buttonState &= 0b10111111;
                break;
            case dpadLeft:
                buttonState &= 0b11011111;
                break;
            case dpadRight:
                buttonState &= 0b11101111;
                break;
            case buttonA:
                buttonState &= 0b11110111;
                break;
            case buttonB:
                buttonState &= 0b11111011;
                break;
            case buttonStart:
                buttonState &= 0b11111101;
                break;
            case buttonSelect:
                buttonState &= 0b11111110;
                break;
        }
    } else {
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
