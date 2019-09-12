#pragma once

namespace cpu {
    class registers {
        private: 
            uint8_t a, b, c, d, e, f, h, l;
            uint16_t sp;
            uint16_t pc; 
        public:
            uint8_t getA();
            uint8_t getB();
            uint8_t getC();
            uint8_t getD();
            uint8_t getE();
            uint8_t getF();
            uint8_t getH();
            uint8_t getL();
            uint16_t getAF();
            uint16_t getBC();
            uint16_t getDE();
            uint16_t getHL();
            void setA(uint8_t a);
            void setB(uint8_t b);
            void setC(uint8_t c);
            void setD(uint8_t d);
            void setE(uint8_t e);
            void setF(uint8_t f);
            void setH(uint8_t h);
            void setL(uint8_t l);
            void setAF(uint16_t af);
            void setBC(uint16_t bc);
            void setDE(uint16_t de);
            void setHL(uint16_t hl);
    };
}
