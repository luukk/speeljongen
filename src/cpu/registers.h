#include "cpuConsts.h"
#pragma once

namespace cpu {
    class Registers {
        private: 
            uint8_t a = 0;
            uint8_t b = 0;
            uint8_t c = 0;
            uint8_t d = 0;
            uint8_t e = 0;
            uint8_t f = 0;
            uint8_t h = 0;
            uint8_t l = 0;
            uint16_t sp = 0x00;
            uint16_t pc = 0x00; 
        public:
            uint8_t getA();
            uint8_t getB();
            uint8_t getC();
            uint8_t getD();
            uint8_t getE();
            uint8_t getF();
            uint8_t getH();
            uint8_t getL();
            uint16_t getBC();
            uint16_t getDE();
            uint16_t getHL();
            uint16_t getSP();
            uint16_t getPC();
            void setA(uint8_t a);
            void setB(uint8_t b);
            void setC(uint8_t c);
            void setD(uint8_t d);
            void setE(uint8_t e);
            void setF(uint8_t f);
            void setH(uint8_t h);
            void setL(uint8_t l);
            void setBC(uint16_t bc);
            void setDE(uint16_t de);
            void setHL(uint16_t hl);
            void setSP(uint16_t sp);
            void setPC(uint16_t pc);
            void incrementPC();
    };
}
