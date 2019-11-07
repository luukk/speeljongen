#include <iostream>
#include "flags.h"

namespace cpu {
    bool Flags::getCarry() {
        return (registerList->getF() >> CARRY_BIT_POSITION) & 0x01;
    }

    bool Flags::getHalfCarry() {
        return (registerList->getF() >> HALF_CARRY_BIT_POSITION) & 0x01;
    }
    
    bool Flags::getSubtract() {
        return (registerList->getF() >> SUB_BIT_POSITION) & 0x01;
    }

    bool Flags::getZero() {
        return(registerList->getF() >> ZERO_BIT_POSITION & 0x01);
    }

    void Flags::setCarry(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, CARRY_BIT_POSITION);
        registerList->setF(flippedBit);
    }

    void Flags::setHalfCarry(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, HALF_CARRY_BIT_POSITION);
        registerList->setF(flippedBit);
    }

    void Flags::setSubtract(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, SUB_BIT_POSITION);
        registerList->setF(flippedBit);
    }

    void Flags::setZero(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, ZERO_BIT_POSITION);
        registerList->setF(flippedBit);
    }

    uint8_t Flags::transformBitPosition(bool bitState, int bitPosition) {
        return (registerList->getF() & ~(1 << bitPosition)) | ((bitState != 0) << bitPosition);
    }
}