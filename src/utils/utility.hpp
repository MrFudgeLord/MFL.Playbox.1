#pragma once

// Project-wide definitions go below

// #define MEM_RAND

// Project-wide helper functions go below

template <typename T>
T ceilingDiv(T dividend, T divisor) {
    return dividend / divisor + (dividend % divisor != 0);
}
