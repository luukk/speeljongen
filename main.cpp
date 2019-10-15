#include <iostream>
#include <memory>
#include "src/gameboy.h"
#include "src/files.h"


int main() {
    auto readBytes = read_bytes("games/tetris.gb");
    std::unique_ptr<Gameboy> gameboy(new Gameboy(readBytes));
    
    gameboy->run();

    int x = 0;
    //24590
    // while(x <=24600) {
    //     gameboy->run();
    //     x++;
    // }
    // tick();
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

