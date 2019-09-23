#include <iostream>
#include "flags.h"
#include "registers.h"

namespace cpu {
    flags::flags(registers* registerList) {
        reg = registerList;
    }

    bool flags::getCarry() {
        return (reg->getF() >> CARRY_BIT_POSITION) & 0x01;
    }

    bool flags::getHalfCarry() {
        return (reg->getF() >> HALF_CARRY_BIT_POSITION) & 0x01;
    }
    
    bool flags::getSubtract() {
        return (reg->getF() >> SUB_BIT_POSITION) & 0x01;
    }

    bool flags::getZero() {
        return(reg->getF() >> ZERO_BIT_POSITION & 0x01);
    }

    void flags::setCarry(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, CARRY_BIT_POSITION);
        reg->setF(flippedBit);
    }

    void flags::setHalfCarry(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, HALF_CARRY_BIT_POSITION);
        reg->setF(flippedBit);
    }

    void flags::setSubtract(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, SUB_BIT_POSITION);
        reg->setF(flippedBit);
    }

    void flags::setZero(bool bit) {
        uint8_t flippedBit = transformBitPosition(bit, ZERO_BIT_POSITION);
        reg->setF(flippedBit);
    }

    uint8_t flags::transformBitPosition(bool bitState, int bitPosition) {
        return (reg->getF() & ~(1 << bitPosition)) | ((bitState != 0) << bitPosition);
    }
}