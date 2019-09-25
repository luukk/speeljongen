#include "../memory/mmu.h"
#include "registers.h"
#include "flags.h"

#include <cstdint>

namespace cpu {
    class CPU {
        public:
            CPU(memory::Mmu *_mmu);
            void tick();
            void excecuteOpcode(uint8_t, uint16_t);
        private:
            memory::Mmu *mmu;
    };
}