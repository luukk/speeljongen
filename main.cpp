#include <iostream>
#include <memory>
#include "src/gameboy.h"
#include "src/files.h"

int main() {
    auto readBytes = read_bytes("games/tetris.gb");
    std::unique_ptr<Gameboy> gameboy(new Gameboy(readBytes));
    
    gameboy->run();

    int ticks = 0;
    //24594
    while(ticks <= 24596) {
        std::cout << "\ntick nr: " << ticks << std::endl;
        gameboy->run();
        ticks++;
    }
}

