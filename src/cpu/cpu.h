#include "../memory/mmu.h"
#include "registers.h"
#include "flags.h"

#include <cstdint>

namespace cpu {
    class CPU {
        public:
            CPU(memory::Mmu *_mmu);
            void tick();
        private:
            memory::Mmu *mmu;
            Registers registerList;
            Flags flags;

            void excecuteOpcode(uint8_t, uint16_t);
            uint8_t fetchOpcode(uint16_t pc);
    };
}