#pragma once


inline bool checkBit(const int value, const int bit) {
    return (value & (1 << bit)) != 0;
}

inline uint8_t bitValue(const uint8_t value, const uint8_t bit) {
    return (value >> bit) & 1;
}

inline bool composeBits(const uint8_t high, const uint8_t low) {
    return static_cast<uint8_t>(high << 1 | low);
}

inline uint16_t composeBytes(const uint8_t high, const uint8_t low) {
    return static_cast<uint16_t>((high << 8) | low);
}

