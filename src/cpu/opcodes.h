#pragma once
#include "registers.h"
#include "../memory/mmu.h"

namespace cpu {
    class Opcodes {
        private: 
            Registers *reg;
            memory::Mmu *mmu;
            void opcodeNop();
            void opcodeLd();
            uint8_t getByteFromPC();
        public:
            Opcodes(Registers* registerList, memory::Mmu* _mmu);
            void opcodeBank(uint8_t);
    };
}