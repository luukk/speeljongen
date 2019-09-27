#include <iostream>
#include "cpu.h"

namespace cpu {
    CPU::CPU(memory::Mmu *_mmu) :
    flags(&registerList)
    {
        mmu = _mmu;
    };

    void CPU::tick() {
        uint16_t pc = registerList.getPC();
        fetchOpcode(pc);
    }

    uint8_t CPU::fetchOpcode(uint16_t pc) {
        uint8_t opcode = mmu->read(pc);
        registerList.incrementPC();

        return opcode;
    }

    void excecuteOpcode(uint8_t, uint16_t) {
        
    }
}