#include <iostream>
#include "registers.h"

namespace cpu { 
    void Registers::setA(uint8_t a) {
        std::cout << "a set";
        this->a = a;
    };

    void Registers::setB(uint8_t b) {
        this->b = b;
    };

    void Registers::setC(uint8_t c) {
        this->c = c;
    };

    void Registers::setD(uint8_t d) {
        this->d = d;
    };

    void Registers::setE(uint8_t e) {
        this->e = e;
    };

    void Registers::setF(uint8_t f) {
        this->f = f;
    };

    void Registers::setH(uint8_t h) {
        this->h = h;
    };

    void Registers::setL(uint8_t l) {
        this->l = l;
    };
    
    void Registers::setBC(uint16_t bc) {
        this->b = (uint8_t)((bc & 0xFF00) >> 8);
        this->c = (uint8_t)(bc & 0x00FF);
    };
  
    void Registers::setDE(uint16_t de) {
        this->d = (uint8_t)((de & 0xFF00) >> 8);
        this->e = (uint8_t)(de & 0x00FF);
    };
  
    void Registers::setHL(uint16_t hl) {
        this->h = (uint8_t)((hl & 0xFF00) >> 8);
        this->l = (uint8_t)(hl & 0x00FF);
    };

    void Registers::setSP(uint16_t sp) {
        this->sp = sp;
    }

    void Registers::incrementPC() {
        this->pc++;
    }
    
    /*  GETTERS */
    uint8_t Registers::getA() {
        std::cout << "a get" << (int)this->a << "\n";

        return this->a;
    };

    uint8_t Registers::getB() {
        return this->b;
    };

    uint8_t Registers::getC() {
        return this->c;
    };

    uint8_t Registers::getD() {
        return this->d;
    };

    uint8_t Registers::getE() {
        return this->e;
    };
    /* for debugging purposes */
    uint8_t Registers::getF() {
        return this->f;
    };

    uint8_t Registers::getH() {
        return this->h;
    };

    uint8_t Registers::getL() {
        return this->l;
    };

    uint16_t Registers::getBC(){
        return ((uint16_t)(this->b) << 8) | this->c;
    };

    uint16_t Registers::getDE(){
        return ((uint16_t)(this->d) << 8) | this->e;
    };

    uint16_t Registers::getHL(){
        return ((uint16_t)(this->h) << 8) | this->l;
    }

    uint16_t Registers::getPC() {
        return this->pc;
    }
    
    uint16_t Registers::getSP() {
        return this->sp;
    }
}

