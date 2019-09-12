#include <iostream>
#include "registers.h"

namespace cpu {
    void registers::setA(uint8_t a) {
        this->a = a;
    };

    void registers::setB(uint8_t b) {
        this->b = b;
    };

    void registers::setC(uint8_t c) {
        this->c = c;
    };

    void registers::setD(uint8_t d) {
        this->d = d;
    };

    void registers::setE(uint8_t e) {
        this->e = e;
    };

    void registers::setF(uint8_t f) {
        this->f = f;
    };

    void registers::setH(uint8_t h) {
        this->h = h;
    };

    void registers::setL(uint8_t l) {
        this->l = l;
    };

    void registers::setAF(uint16_t af) {
        this->a = (uint8_t)((af & 0xFF00) >> 8);
        this->f = (uint8_t)(af & 0x00FF);
    };
    
    void registers::setBC(uint16_t bc) {
        this->b = (uint8_t)((bc & 0xFF00) >> 8);
        this->c = (uint8_t)(bc & 0x00FF);
    };
  
    void registers::setDE(uint16_t de) {
        this->d = (uint8_t)((de & 0xFF00) >> 8);
        this->e = (uint8_t)(de & 0x00FF);
    };
  
    void registers::setHL(uint16_t hl) {
        this->h = (uint8_t)((hl & 0xFF00) >> 8);
        this->l = (uint8_t)(hl & 0x00FF);
    };
    
    /*  GETTERS */
    uint8_t registers::getA() {
        return this->a;
    };

    uint8_t registers::getB() {
        return this->b;
    };

    uint8_t registers::getC() {
        return this->c;
    };

    uint8_t registers::getD() {
        return this->d;
    };

    uint8_t registers::getE() {
        return this->e;
    };

    uint8_t registers::getF() {
        return this->f;
    };

    uint8_t registers::getH() {
        return this->h;
    };

    uint8_t registers::getL() {
        return this->l;
    };

    uint16_t registers::getAF(){
        return ((uint16_t)(this->a) << 8) | this->f;
    };

    uint16_t registers::getBC(){
        return ((uint16_t)(this->b) << 8) | this->c;
    };

    uint16_t registers::getDE(){
        return ((uint16_t)(this->d) << 8) | this->e;
    };

    uint16_t registers::getHL(){
        return ((uint16_t)(this->h) << 8) | this->l;
    }
}

