#include "dummy.hpp"
#include "SDL3/SDL_timer.h"
#include "scheduler.hpp"
#include <SDL3/SDL.h>

namespace scheduler {
extern scheduledDevice  *devices[32];
extern processor        *processors[16];
extern displayProcessor *displayProcessorPtr;
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

bool dummy::dispatchEvent(uint8_t index, uint8_t data[4]) {
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
    return false;
}

void dummy::frameEnd(uint8_t data[4]) {
    using namespace scheduler;
    frameEventQueue.push({deviceID, 0, CLOCKS_PER_FRAME});
    puts("Pushed next frameEnd\n");
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
    mainClock = 0;
    for(processor *p : processors) {
        if(p) p->eventClock = 0;
    }
    puts("Passed while loop\n");
    nextEventClock = frameEventQueue.top().timeSeq;
    puts("Set nextEventClock\n");

    SDL_UpdateTexture(context.texture, nullptr, frameBuffer, 768 * 4);
    SDL_RenderClear(context.renderer);
    SDL_RenderTexture(context.renderer, context.texture, nullptr, nullptr);
    SDL_RenderPresent(context.renderer);

    // while((SDL_GetTicksNS() - lastFrameEndns) < 16'666'667);
    // lastFrameEndns = SDL_GetTicksNS();
    return;
}

void dummy::debugger(uint8_t data[4]) {
    mb->nmiLine.val = false;
    return;
}
