#include <iostream>
#include "cpu.h"

namespace cpu {
    CPU::CPU(memory::Mmu *_mmu) :
    flags(&registerList),
    opcodes(&registerList, &flags, _mmu)
    {
        mmu = _mmu;
    };

    void CPU::tick() {
        uint16_t pc = registerList.getPC();
        auto opcode = fetchOpcode(pc);
        excecuteOpcode(opcode);
    }

    uint8_t CPU::fetchOpcode(uint16_t pc) {
        std::cout << "CPU::fetchOpcode pc: " << pc << '\n';
        uint8_t opcode = mmu->read(pc);
        registerList.incrementPC();

        return opcode;
    }

    void CPU::excecuteOpcode(uint8_t opcode) {
        opcodes.opcodeBank(opcode);
    }
}