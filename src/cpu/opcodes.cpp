#include <iostream>
#include <functional>
#include "opcodes.h"
#include "../bitUtils.h"

namespace cpu {
    bool blockInterrupts = false;

    Opcodes::Opcodes() {
        std::cout << "opcode init";
        std::cout << registerList->getPC() << "\n";
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
            case 0xCD:opcodeCall();break;
            case 0x1A:opcodeLd(&Registers::setA, &Registers::getDE);break;
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
        std::cout << "opcodeLd\n";
        uint8_t byte = getByteFromPC();

        std::invoke(setRegister, registerList, byte);
    }

    void Opcodes::opcodeLd(void (Registers::*setRegister)(uint16_t)) {
        uint8_t lowByte = getByteFromPC();
        uint8_t highByte = getByteFromPC();

        uint16_t composedBytes = static_cast<uint16_t>((highByte << 8) | lowByte);

        std::invoke(setRegister, registerList, composedBytes);
    }

    void Opcodes::opcodeLd(uint16_t (cpu::Registers::*addressRegister)(), uint8_t (cpu::Registers::*registerValue)()) {
        uint16_t address = std::invoke(addressRegister, registerList);
        uint8_t byte = std::invoke(registerValue, registerList);

        mmu->write(address,byte);
    }

    void Opcodes::opcodeLd(void (cpu::Registers::*addressRegister)(uint8_t), uint16_t (cpu::Registers::*registerValue)()) {
        uint16_t val = std::invoke(registerValue, registerList);
        uint8_t memoryValue = mmu->read(val);
        std::cout << "yeeeeeeeeeeeeeeeeeeeeeee\n";

        std::invoke(addressRegister, registerList, memoryValue);
    }

    void Opcodes::opcodeCall() {
        std::cout << "opcodeCall \n";
        uint8_t lowByte = getByteFromPC();
        uint8_t highByte = getByteFromPC();

        cpu::stackPush(lowByte, highByte);

        std::cout << "Opcodes::opcodeCall lowByte\n" << unsigned(lowByte);
        std::cout << "Opcodes::opcodeCall highByte\n" << unsigned(highByte);
    }

    /**XOR**/

    void Opcodes::_opcodeXor(uint8_t value) {
        std::cout << "Opcodes::opcodeXor setting " << unsigned(value) << " in register a\n";
        uint8_t regAValue = registerList->getA();
        uint8_t result = regAValue ^ value;

        flags->setZero(result);
        flags->setSubtract(false);
        flags->setHalfCarry(false);
        flags->setCarry(false);

        registerList->setA(result);
    }

    void Opcodes::opcodeXor(uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t regAValue = std::invoke(registerValue, registerList);
        _opcodeXor(regAValue);
    }

    /**LDH**/
    
    void Opcodes::opcodeLdhIntoA() {
        uint8_t regCValue = registerList->getC();
        auto address = 0xFF00 + regCValue;

        mmu->write(address,registerList->getA());
    }

    void Opcodes::opcodeLdhIntoData() {
        uint8_t offset = getByteFromPC();
        auto address = 0xFF00 + offset;

        mmu->write(address, registerList->getA());
    }

    /**INC**/

    void Opcodes::_opcodeInc(void (cpu::Registers::*setRegister)(uint8_t), uint8_t registerValue) {
        auto increment = registerValue++;
        std::invoke(setRegister, registerList, increment);
    }

    void Opcodes::opcodeInc(void (cpu::Registers::*setRegister)(uint8_t), uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t value = std::invoke(registerValue, registerList);
        _opcodeInc(setRegister, value);

        flags->setZero(value == 0);
        flags->setSubtract(false);
        flags->setHalfCarry((value & 0x0F) == 0x00);
    }

    /**LDD**/

    void Opcodes::opcodeLdd(uint16_t (cpu::Registers::*addressRegister)(), uint8_t (cpu::Registers::*registerValue)()) {
        uint16_t address = std::invoke(addressRegister, registerList);
        uint8_t byte = std::invoke(registerValue, registerList);

        mmu->write(address,byte);

        registerList->setHL(registerList->getHL()-1); //decrement hl register
    }

    /**BIT**/

    void Opcodes::_opcodeBit(const uint8_t bit, const uint8_t registerValue) {
        flags->setZero(!checkBit(registerValue, bit));
        flags->setSubtract(false);
        flags->setHalfCarry(true);
    }
    
    void Opcodes::opcodeBit(const uint8_t bit, uint8_t (cpu::Registers::*registerValue)()) {
        uint8_t regValue = std::invoke(registerValue, registerList);
        _opcodeBit(bit, regValue);
    };

    /**JUMP**/

    void Opcodes::opcodeJr() {
        int8_t offset = getSignedByteFromPC();
        uint16_t pc = registerList->getPC();

        std::cout << "opcodeJR program counter: " << static_cast<uint16_t>(pc) << "\n";
        std::cout << "opcodJR offset: " <<  static_cast<int16_t>(offset) << "\n"; 
        std::cout << "opcodJR new pc location: " <<  static_cast<uint16_t>(pc + offset) << "\n"; 
        std::cout << "opcodeJR hl: " << static_cast<uint16_t>(registerList->getHL()) << "\n";
        
        uint16_t newPC =  static_cast<uint16_t>(pc + offset);
        std::cout << "opcodeJR newPC: " << static_cast<uint16_t>(newPC) << "\n";

        registerList->setPC(newPC);
    }

    void Opcodes::opcodeJr(Condition condition) {
        if(shouldBranch(condition)) {
            opcodeJr();
        } else {
            /* /null/dev argument */
            getSignedByteFromPC();
        }
        std::cout << "opcodeJr flag stat: " << flags->getZero() << "\n";
    }

    /**INTERRUPTS**/

    void Opcodes::opcodeDisableInterrupt() {
        // cpu::blockInterrupts = true;
    }


    uint8_t Opcodes::getByteFromPC() {
        uint16_t pc = registerList->getPC();
        uint8_t byte = mmu->read(pc);

        std::cout << "getByteFromPC byte: " << unsigned(byte) << "\n"; 
        
        registerList->incrementPC();

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
            shouldBranch = flags->getCarry();
            break;
        case Condition::NC:
            shouldBranch = !flags->getCarry();
            break;
        case Condition::Z:
            shouldBranch = flags->getZero();
            break;
        case Condition::NZ:
            shouldBranch = !flags->getZero();
            break;
        }

        return shouldBranch;
    }
}
