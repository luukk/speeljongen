#include "registers.h"
#pragma once

namespace cpu {
    class flags {
        private:
            registers *reg;
        public:
            flags(registers& registerList);
            uint8_t getCarry();
            uint8_t getHalfCarry();
            uint8_t getSubtract();
            uint8_t getZero();
            void setCarry();
            void setHalfCarry();
            void setSubtract();
            void setZero();
    };
}
