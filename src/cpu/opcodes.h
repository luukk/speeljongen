#pragma once
#include "registers.h"
#include "../memory/mmu.h"
#include "flags.h"

namespace cpu {
    class Opcodes {
        private: 
            Registers *reg;
            memory::Mmu *mmu;
            Flags *flag;
            
            void opcodeNop();
            void opcodeLd();
            void opcodeXor(uint8_t (cpu::Registers::*)());
            void _opcodeXor(uint8_t);
            uint8_t getByteFromPC();
        public:
            Opcodes(Registers* registerList, Flags* flags, memory::Mmu* _mmu);
            void opcodeBank(uint8_t);
    };
}