#include <iostream>
#include <memory>
#include "src/gameboy.h"



int main() {
    std::unique_ptr<Gameboy> gameboy(new Gameboy());

    // gameboy();
    // cpu::registers registerList;
    // cpu::flags flagSet(&registerList);


    // flagSet.setCarry(0);
    // flagSet.setZero(1);

    // flagSet.getCarry();
    // std::cout << unsigned(registerList.getF());

    // flagSet->setCarry();
    // std::cout << *registerList;
    // flags.setCarry();
    // flags.getCarry();
}

