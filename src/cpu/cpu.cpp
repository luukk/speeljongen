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
        std::cout << "\nnew tick \n";
        uint16_t pc = registerList.getPC();
        uint8_t opcode = fetchOpcode(pc);

        if(opcode == 0xCB) { //cb opcode initializer
            std::cout << "fetching additional instruction set opcode\n";
            
            uint16_t pc = registerList.getPC();
            uint8_t cbOpcode = fetchOpcode(pc);
            
            excecuteCBOpcode(cbOpcode);
            return;
        }

        excecuteOpcode(opcode);
    }

    uint8_t CPU::fetchOpcode(uint16_t pc) {   
        uint8_t opcode = mmu->read(pc);
        registerList.incrementPC();

        return opcode;
    }

    void CPU::excecuteOpcode(uint8_t opcode) {
        opcodes.opcodeBank(opcode);
    }

    void CPU::excecuteCBOpcode(uint8_t opcode) {
        opcodes.cbOpcodeBank(opcode);
    }
}