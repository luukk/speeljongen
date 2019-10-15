#include <iostream>
#include "opcodes.h"
#include "../bitUtils.h"

namespace cpu {
    bool blockInterrupts = false;

    Opcodes::Opcodes(Registers* _reg, Flags* _flag, memory::Mmu* _mmu) {
        reg = _reg;
        flag = _flag;
        mmu = _mmu;
    }
    void Opcodes::opcodeBank(uint8_t opcode) {
        switch (opcode) {
            case 0x00:opcodeNop();break;
            case 0x0C:opcodeInc(&Registers::setC, &Registers::getC);break;
            case 0x0E:opcodeLd(&Registers::setC);break;
            case 0x11:opcodeLd(&Registers::setDE);break;
            case 0x20:opcodeJr(Condition::NZ);break;
            case 0x21:opcodeLd(&Registers::setHL);break;
            case 0x31:opcodeLd(&Registers::setSP);break;
            case 0x32:opcodeLdd(&Registers::getHL, &Registers::getA);break;
            case 0x3E:opcodeLd(&Registers::setA);break;
            case 0x77:opcodeLd(&Registers::getHL, &Registers::getA);
            case 0xAF:opcodeXor(&Registers::getA);break;
            case 0xE0:opcodeLdhIntoData();break;
            case 0x1A:opcodeLd(&Registers::getA, &Registers::getDE);break;
            case 0xE2:opcodeLdhIntoA();break;
            case 0xF3:opcodeDisableInterrupt();break;
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

    void Opcodes::opcodeLd(uint16_t (cpu::Registers::*addressRegister)(), uint8_t (cpu::Registers::*registerValue)()) {
        uint16_t address = (reg->*addressRegister)();
        uint8_t byte = (reg->*registerValue)();

        mmu->write(address,byte);
    }

    void Opcodes::opcodeLd(uint8_t (cpu::Registers::*addressRegister)(), uint16_t (cpu::Registers::*registerValue)()) {
        uint16_t val = (reg->*registerValue)();
        // auto memoryValue = mmu->read(val);

        std::cout << "yeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee: " << unsigned(val); 
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

    void Opcodes::opcodeLdhIntoData() {
        uint8_t offset = getByteFromPC();
        auto address = 0xFF00 + offset;

        mmu->write(address, reg->getA());
    }

    /**INC**/

    void Opcodes::_opcodeInc(void (cpu::Registers::*setRegister)(uint8_t), uint8_t registerValue) {
        auto increment = registerValue++;
        (reg->*setRegister)(increment);
    }

    void Opcodes::opcodeInc(void (cpu::Registers::*setRegister)(uint8_t), uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t value = (reg->*registerValue)();
        _opcodeInc(setRegister, value);

        flag->setZero(value == 0);
        flag->setSubtract(false);
        flag->setHalfCarry((value & 0x0F) == 0x00);
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

    /**JUMP**/

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

    /**INTERRUPTS**/

    void Opcodes::opcodeDisableInterrupt() {
        cpu::blockInterrupts = true;
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
