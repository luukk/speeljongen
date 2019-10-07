#pragma once
#include "registers.h"
#include "../memory/mmu.h"
#include "flags.h"



namespace cpu {
    bool blockInterrupts = false;
    enum class Condition {
        NZ,
        Z,
        NC,
        C,
    };
    class Opcodes {
        private: 
            Registers *reg;
            memory::Mmu *mmu;
            Flags *flag;
            
            void opcodeNop();
            void opcodeLd(void (cpu::Registers::*)(uint8_t));
            void opcodeLd(void (cpu::Registers::*)(uint16_t));
            void opcodeLd(uint16_t (cpu::Registers::*)(), uint8_t (cpu::Registers::*)());
            void opcodeXor(uint8_t (cpu::Registers::*)());
            void opcodeLdd(uint16_t (cpu::Registers::*)(), uint8_t (cpu::Registers::*)());
            void opcodeJr();
            void opcodeJr(Condition);        
            void _opcodeXor(uint8_t);
            void _opcodeBit(const uint8_t bit, const uint8_t);
            void opcodeBit(const uint8_t, uint8_t (cpu::Registers::*)());
            void opcodeLdhIntoA();
            void opcodeLdhIntoData();
            void _opcodeInc(void (cpu::Registers::*)(uint8_t), uint8_t);
            void opcodeInc(void (cpu::Registers::*)(uint8_t), uint8_t (cpu::Registers::*)());  
            void opcodeDisableInterrupt();
            uint8_t getByteFromPC();
            int8_t getSignedByteFromPC();
            bool shouldBranch(Condition);
        public:
            Opcodes(Registers* registerList, Flags* flags, memory::Mmu* _mmu);
            void opcodeBank(uint8_t);
            void cbOpcodeBank(uint8_t);
    };
}

