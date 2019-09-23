#include <iostream>
#include "src/cpu/registers.h"
#include "src/cpu/flags.h"
#include "src/memory/mmu.h"

int main() {
    // cpu::registers registerList;
    // cpu::flags flagSet(&registerList);
    memory::mmu mmu;

    mmu.read(0x8000, 20);

    // flagSet.setCarry(0);
    // flagSet.setZero(1);

    // flagSet.getCarry();
    // std::cout << unsigned(registerList.getF());

    // flagSet->setCarry();
    // std::cout << *registerList;
    // flags.setCarry();
    // flags.getCarry();
}

