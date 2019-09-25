#include <iostream>
#include "cpu.h"

namespace cpu {
    CPU::CPU(memory::Mmu *_mmu) {
        mmu = _mmu;
    };
}