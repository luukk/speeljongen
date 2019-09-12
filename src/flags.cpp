#include <iostream>
#include "flags.h"
#include "registers.h"

namespace cpu {
    flags::flags(registers& registerList) {
        reg = &registerList;
    }

    void flags::setCarry() {
        reg->setF(10);
    }
}