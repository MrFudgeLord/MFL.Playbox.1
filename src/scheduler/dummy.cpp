#include "dummy.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_timer.h"
#include "scheduler.hpp"
#include <SDL3/SDL.h>
#include <iostream>

namespace scheduler {
extern scheduledDevice  *devices[32];
extern processor        *processorPtr;
extern displayProcessor *displayProcessorPtr;
extern inputDevice      *inputDevicePtr;
} // namespace scheduler

dummy::dummy(M1000 *mbptr, SDLContext sdl) {
    deviceID                                    = 0;
    scheduler::devices[0]                       = this;
    mb                                          = mbptr;
    context                                     = sdl;
    scheduler::displayProcessorPtr->frameBuffer = frameBuffer;
    scheduler::frameEventQueue.push({deviceID, 0, scheduler::CLOCKS_PER_FRAME});
    lastFrameEndns = SDL_GetTicksNS();
}

uint32_t dummy::dispatchEvent(uint8_t index, uint8_t data[4]) {
    static void (dummy::*eventHandlers[8])(uint8_t[4]) = {
        &dummy::frameEnd,
        &dummy::debugger,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    (this->*eventHandlers[index])(data);
    return 0;
}

void dummy::frameEnd(uint8_t data[4]) {
    using namespace scheduler;
    frameEventQueue.push({deviceID, 0, CLOCKS_PER_FRAME});
    while(!futureEventQueue.empty()) {
        event futureEvent    = futureEventQueue.top();
        futureEvent.timeSeq -= CLOCKS_PER_FRAME;
        if(futureEvent.timeSeq < CLOCKS_PER_FRAME) {
            frameEventQueue.push(futureEvent);
            futureEventQueue.pop();
        } else {
            break;
        }
    }
    mainClock                = 0;
    processorPtr->eventClock = 0;
    nextEventClock           = frameEventQueue.top().timeSeq;

    SDL_UpdateTexture(context.texture, nullptr, frameBuffer, 768 * 4);
    SDL_RenderClear(context.renderer);
    SDL_RenderTexture(context.renderer, context.texture, nullptr, nullptr);
    SDL_RenderPresent(context.renderer);

    inputDevicePtr->resetInput();

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                exit(0);
                break;
            case SDL_EVENT_KEY_DOWN: {
                keyboardEvent kbe;
                kbe.keycode = event.key.key;
                kbe.mods    = event.key.mod;
                kbe.keyUp   = false;
                kbe.repeat  = event.key.repeat;
                inputDevicePtr->handleKeyboard(kbe);
                break;
            }
        }
    }

    SDL_Log("ns left in frame: %llu\n", lastFrameEndns + 16'666'667 - SDL_GetTicksNS());
    if(lastFrameEndns + 16'666'667 - SDL_GetTicksNS() > 16'666'667) {
        std::cin.get();
        exit(0x10);
    }

    while((SDL_GetTicksNS() - lastFrameEndns) < 16'666'667);
    lastFrameEndns = SDL_GetTicksNS();
    return;
}

void dummy::debugger(uint8_t data[4]) {
    mb->nmiLine.val = false;
    return;
}
