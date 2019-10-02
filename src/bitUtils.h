#pragma once


inline bool checkBit(const int value, const int bit) {
    return (value & (1 << bit)) != 0;
}
