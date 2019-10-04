#include <iostream>
#include "opcodes.h"
#include "../bitUtils.h"

namespace cpu {
    Opcodes::Opcodes(Registers* _reg, Flags* _flag, memory::Mmu* _mmu) {
        reg = _reg;
        flag = _flag;
        mmu = _mmu;
    }
    void Opcodes::opcodeBank(uint8_t opcode) {
        switch (opcode) {
            case 0x00:opcodeNop();break;
            case 0x0E:opcodeLd(&Registers::setC);break;
            case 0x20:opcodeJr(Condition::NZ);break;
            case 0x21:opcodeLd(&Registers::setHL);break;
            case 0x31:opcodeLd(&Registers::setSP);break;
            case 0x32:opcodeLdd(&Registers::getHL, &Registers::getA);break;
            case 0x3E:opcodeLd(&Registers::setA);break;
            case 0xAF:opcodeXor(&Registers::getA);break;
            case 0xE2:opcodeLdhIntoA();break;
        }
    }

    void Opcodes::cbOpcodeBank(uint8_t opcode) {
        switch (opcode) {
            case 0x7C: opcodeBit(7, &Registers::getH);break;
        }
    }

    void Opcodes::opcodeNop() {
        std::cout << "nop opcode called";
        return;
    }

    /**LOAD**/

    void Opcodes::opcodeLd(void (cpu::Registers::*setRegister)(uint8_t)) {
       uint8_t byte = getByteFromPC();

       (reg->*setRegister)(byte);
    }

    void Opcodes::opcodeLd(void (cpu::Registers::*setRegister)(uint16_t)) {
        uint8_t lowByte = getByteFromPC();
        uint8_t highByte = getByteFromPC();

        uint16_t composedBytes = static_cast<uint16_t>((highByte << 8) | lowByte);
        (reg->*setRegister)(composedBytes);
    }

    /**XOR**/

    void Opcodes::_opcodeXor(uint8_t value) {
        std::cout << "Opcodes::opcodeXor setting " << unsigned(value) << " in register a\n";
        uint8_t regAValue = reg->getA();
        uint8_t result = regAValue ^ value;

        flag->setZero(result);
        flag->setSubtract(false);
        flag->setHalfCarry(false);
        flag->setCarry(false);

        reg->setA(result);
    }

    void Opcodes::opcodeXor(uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t regAValue = (reg->*registerValue)();
        _opcodeXor(regAValue);
    }

    /**LDH**/
    void Opcodes::opcodeLdhIntoA() {
        uint8_t regCValue = reg->getC();
        auto address = 0xFF00 + regCValue;

        mmu->write(address,reg->getA());
    }

    /**LDD**/

    void Opcodes::opcodeLdd(uint16_t (cpu::Registers::*addressRegister)(), uint8_t (cpu::Registers::*registerValue)()) {
        uint16_t address = (reg->*addressRegister)();
        uint8_t byte = (reg->*registerValue)();

        mmu->write(address,byte);

        reg->setHL(reg->getHL()-1); //decrement hl register
    }

    /**BIT**/

    void Opcodes::_opcodeBit(const uint8_t bit, const uint8_t registerValue) {
        flag->setZero(!checkBit(registerValue, bit));
        flag->setSubtract(false);
        flag->setHalfCarry(true);
    }
    
    void Opcodes::opcodeBit(const uint8_t bit, uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t regValue = (reg->*registerValue)();
        _opcodeBit(bit, regValue);
    };

    void Opcodes::opcodeJr() {
        int8_t offset = getSignedByteFromPC();
        uint16_t pc = reg->getPC();

        std::cout << "opcodJR offset: " <<  static_cast<int16_t>(offset) << "\n"; 
        std::cout << "opcodJR new pc location: " <<  static_cast<uint16_t>(pc + offset) << "\n"; 
        std::cout << "opcodeJR hl: " << static_cast<uint16_t>(reg->getHL()) << "\n";
        uint16_t newPC =  static_cast<uint16_t>(pc + offset);
        reg->setPC(newPC);
    }

    void Opcodes::opcodeJr(Condition condition) {
        if(shouldBranch(condition)) {
            opcodeJr();
        } else {
            /* /null/dev argument */
            getSignedByteFromPC();
        }
        std::cout << "opcodeJr flag stat: " << flag->getZero() << "\n";
    }


    uint8_t Opcodes::getByteFromPC() {
        uint16_t pc = reg->getPC();
        uint8_t byte = mmu->read(pc);

        std::cout << "getByteFromPC byte: " << unsigned(byte) << "\n"; 
        
        reg->incrementPC();

        return byte;
    }

    int8_t Opcodes::getSignedByteFromPC() {
        int8_t byte = getByteFromPC();
        return static_cast<int8_t>(byte);
    }

    bool Opcodes::shouldBranch(Condition condition) {
        bool shouldBranch;

        switch (condition) {
        case Condition::C:
            shouldBranch = flag->getCarry();
            break;
        case Condition::NC:
            shouldBranch = !flag->getCarry();
            break;
        case Condition::Z:
            shouldBranch = flag->getZero();
            break;
        case Condition::NZ:
            shouldBranch = !flag->getZero();
            break;
        }

        return shouldBranch;
    }
}
