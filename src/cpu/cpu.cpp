#include <iostream>
#include "cpu.h"

namespace cpu {
    std::unique_ptr<Registers> registerList;
    std::unique_ptr<Flags> flags;
    std::unique_ptr<Opcodes> opcodes;
    std::shared_ptr<memory::Mmu> mmu;

    CPU::CPU(std::shared_ptr<memory::Mmu> &_mmu)
        {
            std::cout << "cpu init\n";

            cpu::mmu = _mmu;
            cpu::registerList = std::make_unique<Registers>();
            cpu::flags = std::make_unique<Flags>();
            cpu::opcodes = std::make_unique<Opcodes>();
        };

    void CPU::tick() {
        std::cout << "\nnew tick \n";
        uint16_t pc = registerList->getPC();
        uint8_t opcode = fetchOpcode(pc);

        if(opcode == 0xCB) { //cb opcode initializer
            std::cout << "fetching additional instruction set opcode\n";
            
            uint16_t pc = registerList->getPC();
            uint8_t cbOpcode = fetchOpcode(pc);
            
            excecuteCBOpcode(cbOpcode);
            return;
        }

        excecuteOpcode(opcode);
    }

    uint8_t CPU::fetchOpcode(uint16_t pc) {   
        uint8_t opcode = mmu->read(pc);
        registerList->incrementPC();
        return opcode;
    }

    void CPU::excecuteOpcode(uint8_t opcode) {
        opcodes->opcodeBank(opcode);
    }

    void CPU::excecuteCBOpcode(uint8_t opcode) {
        opcodes->cbOpcodeBank(opcode);
    }

    /* cpu namespace */
    
    void stackPush(uint8_t lowByte, uint8_t highByte) {

        std::cout << "stackPush\n";
    }
}