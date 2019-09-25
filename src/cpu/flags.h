#pragma once
#include "registers.h"

#define CARRY_BIT_POSITION 5
#define HALF_CARRY_BIT_POSITION 6
#define SUB_BIT_POSITION 7
#define ZERO_BIT_POSITION 4

namespace cpu {
    class Flags {
        private:
            Registers *reg;
            uint8_t transformBitPosition(bool, int);
        public:
            Flags(Registers* registerList);
            bool getCarry();
            bool getHalfCarry();
            bool getSubtract();
            bool getZero();
            void setCarry(bool);
            void setHalfCarry(bool);
            void setSubtract(bool);
            void setZero(bool);
    };
}