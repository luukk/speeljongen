#include <iostream>
#include <memory>
#include "src/gameboy.h"
#include "src/files.h"

int main() {
    auto readBytes = read_bytes("games/tetris.gb");
    std::unique_ptr<Gameboy> gameboy(new Gameboy(readBytes));
    
    gameboy->run();

    int x = 0;
    //24594
    while(x <= 24594) {
        gameboy->run();
        x++;
    }
}

