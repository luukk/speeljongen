#include <iostream>
#include "opcodes.h"

namespace cpu {
    Opcodes::Opcodes(Registers* _reg, Flags* _flag, memory::Mmu* _mmu) {
        reg = _reg;
        flag = _flag;
        mmu = _mmu;
    }
    void Opcodes::opcodeBank(uint8_t opcode) {
        std::cout << "opcode bank opcode: " << int(opcode) << "\n";
        opcode = 0xAF;
        switch (opcode) {
            case 0x00:opcodeNop();break;
            case 0x31:opcodeLd();break;
            case 0xAF:opcodeXor(&Registers::getA);break;
        }
    }

    void Opcodes::opcodeNop() {
        std::cout << "nop opcode called";
        return;
    }

    /**LOAD**/

    void Opcodes::opcodeLd() {
        uint8_t lowByte = getByteFromPC();
        uint8_t highByte = getByteFromPC();

        uint16_t composedBytes = static_cast<uint16_t>((highByte << 8) | lowByte);
        reg->setSP(composedBytes);
    }

    /**XOR**/

    void Opcodes::_opcodeXor(uint8_t value) {
        uint8_t regAValue = reg->getA();
        uint8_t result = regAValue ^ value;

        flag->setZero(result);
        flag->setSubtract(false);
        flag->setHalfCarry(false);
        flag->setCarry(false);

        reg->setA(result);
    }

    void Opcodes::opcodeXor(uint8_t (cpu::Registers::*getValue)()) {
        uint8_t regAValue = (reg->*getValue)();
        _opcodeXor(regAValue);
    }

    uint8_t Opcodes::getByteFromPC() {
        uint16_t pc = reg->getPC();
        uint8_t byte = mmu->read(pc);
        
        reg->incrementPC();

        return byte;
    }
}
