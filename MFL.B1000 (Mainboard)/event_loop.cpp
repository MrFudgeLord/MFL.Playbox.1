#include "event_loop.hpp"
#include <iostream>

bool operator<(event lhs, event rhs) {
    if(lhs.time != rhs.time) {
        return lhs.time > rhs.time;
    } else {
        assert(lhs.seq != rhs.seq);
        return lhs.seq > rhs.seq;
    }
}
