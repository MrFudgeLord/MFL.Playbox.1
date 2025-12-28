#include "dummy.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_timer.h"
#include "scheduler.hpp"
#include <SDL3/SDL.h>
#include <iostream>

namespace scheduler {
extern scheduledDevice  *devices[256];
extern processor        *processorPtr;
extern displayProcessor *displayProcessorPtr;
extern inputDevice      *inputDevicePtr;
} // namespace scheduler

dummy::dummy(SDLContext sdl) {
    deviceID                                    = 0;
    scheduler::devices[0]                       = this;
    context                                     = sdl;
    scheduler::displayProcessorPtr->frameBuffer = frameBuffer;
    scheduler::scheduleEvent({scheduler::TICKS_PER_FRAME, deviceID, 0});
    // scheduler::scheduleEvent({1, deviceID, 1});
    lastFrameEndns = SDL_GetTicksNS();
}

uint64_t dummy::dispatchEvent(uint8_t index, uint8_t data[4]) {
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
    eventQueue.push({scheduler::mainClock + scheduler::TICKS_PER_FRAME, deviceID, 0});

    SDL_UpdateTexture(context.texture, nullptr, frameBuffer, 768 * 4);
    SDL_RenderClear(context.renderer);
    SDL_RenderTexture(context.renderer, context.texture, nullptr, nullptr);
    SDL_RenderPresent(context.renderer);

    // inputDevicePtr->resetInput();

    static uint32_t numFrames           = 0;
    static uint64_t nsLeftPerFrameTotal = 0;

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                SDL_Log("Average ns left per frame: %lli", nsLeftPerFrameTotal / numFrames);
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

    nsLeftPerFrameTotal += lastFrameEndns + 16'666'667 - SDL_GetTicksNS();
    numFrames++;

    // SDL_Log("ns left in frame: %llu\n", lastFrameEndns + 16'666'667 - SDL_GetTicksNS());
    //  if(lastFrameEndns + 16'666'667 - SDL_GetTicksNS() > 16'666'667) {
    //      std::cin.get();
    //      exit(0x10);
    //  }

    while((SDL_GetTicksNS() - lastFrameEndns) < 16'666'667);
    lastFrameEndns = SDL_GetTicksNS();
    return;
}

void dummy::debugger(uint8_t data[4]) {
    scheduler::scheduleEvent({scheduler::mainClock + 1, deviceID, 1});
    return;
}
