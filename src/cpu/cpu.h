#include "../memory/mmu.h"
#include "registers.h"
#include "flags.h"
#include "opcodes.h"

#include <cstdint>

namespace cpu {
    class CPU {
        public:
            CPU(memory::Mmu *_mmu);
            void tick();
            uint8_t getByteFromPC();
        private:
            memory::Mmu *mmu;
            Registers registerList;
            Flags flags;
            Opcodes opcodes;

            void excecuteOpcode(uint8_t);
            void excecuteCBOpcode(uint8_t);
            uint8_t fetchOpcode(uint16_t pc);
    };
}