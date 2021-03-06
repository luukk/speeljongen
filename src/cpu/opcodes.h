#pragma once
#include "cpuConsts.h"
#include "registers.h"
#include "../memory/mmu.h"
#include "flags.h"



namespace cpu {

    enum class Condition {
        NZ,
        Z,
        NC,
        C,
    };

    class Opcodes {
        private:            
            void opcodeNop();
            void opcodeLd(void (cpu::Registers::*)(uint8_t));
            void opcodeLd(void (cpu::Registers::*)(uint16_t));
            void opcodeLd(uint16_t (cpu::Registers::*)(), uint8_t (cpu::Registers::*)());
            void opcodeLd(void (cpu::Registers::*)(uint8_t), uint16_t (cpu::Registers::*)());
            void opcodeXor(uint8_t (cpu::Registers::*)());
            void opcodeLdd(uint16_t (cpu::Registers::*)(), uint8_t (cpu::Registers::*)());
            void opcodeJr();
            void opcodeJr(Condition);        
            void _opcodeXor(uint8_t);
            void _opcodeBit(const uint8_t bit, const uint8_t);
            void opcodeBit(const uint8_t, uint8_t (cpu::Registers::*)());
            void opcodeLdhIntoA();
            void opcodeLdhIntoData();
            void opcodeInc(uint16_t (cpu::Registers::*)());
            void _opcodeInc(void (cpu::Registers::*)(uint8_t), uint8_t);
            void opcodeInc(void (cpu::Registers::*)(uint8_t), uint8_t (cpu::Registers::*)());  
            void opcodeDisableInterrupt();
            void opcodeCall();
            uint8_t getByteFromPC();
            int8_t getSignedByteFromPC();
            bool shouldBranch(Condition);
        public:
            Opcodes();
            void opcodeBank(uint8_t);
            void cbOpcodeBank(uint8_t);
    };
}

