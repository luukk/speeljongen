#pragma once
#include "cpuConsts.h"
#include "../memory/mmu.h"
#include "registers.h"
#include "flags.h"
#include "opcodes.h"

#include <cstdint>

namespace cpu {
    extern bool blockInterrupts;

    class CPU {
        public:
            CPU(std::shared_ptr<memory::Mmu>&);
            void tick();
            uint8_t getByteFromPC();
        private:
            void excecuteOpcode(uint8_t);
            void excecuteCBOpcode(uint8_t);
            uint8_t fetchOpcode(uint16_t pc);
    };
}