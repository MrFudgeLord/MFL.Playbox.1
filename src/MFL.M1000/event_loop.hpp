#pragma once

#include <functional>
#include <queue>
#include <cassert>

struct event {
    uint32_t              time;
    uint8_t               seq;
    enum device : uint8_t device;
    enum type : uint8_t   type;
    uint8_t               reserved;
};

bool operator<(event, event);

std::priority_queue<event, std::vector<event>> eventQueue;
