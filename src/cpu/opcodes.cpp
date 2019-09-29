#include <iostream>
#include "opcodes.h"

namespace cpu {
    Opcodes::Opcodes(Registers* _reg, memory::Mmu* _mmu) {
        std::cout << "opcode consturtor: " << &_mmu;
        reg = _reg;
        mmu = _mmu;
    }
    void Opcodes::opcodeBank(uint8_t opcode) {
        std::cout << "opcode bank opcode: " << int(opcode) << "\n";
        switch (opcode) {
            case 0x00:opcodeNop();break;
            case 0x31:opcodeLd();break;
        }
    }

    void Opcodes::opcodeNop() {
        std::cout << "nop opcode called";
        return;
    }

    void Opcodes::opcodeLd() {
        uint8_t lowByte = getByteFromPC();
        uint8_t highByte = getByteFromPC();

        uint16_t composedBytes = static_cast<uint16_t>((highByte << 8) | lowByte);
        reg->setSP(composedBytes);
    }

    uint8_t Opcodes::getByteFromPC() {
        uint16_t pc = reg->getPC();
        uint8_t byte = mmu->read(pc);
        
        reg->incrementPC();

        return byte;
    }
}
