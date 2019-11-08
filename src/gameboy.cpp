#include <iostream>
#include <vector>
#include "gameboy.h"

Gameboy::Gameboy(std::vector<uint8_t> cartridgeData) 
    :cartridge(getCartridge(std::move(cartridgeData))),
     mmu(std::make_shared<memory::Mmu>(cartridge)),
     cpu(std::make_unique<cpu::CPU>(mmu))
    {
        std::cout << "cpu mmutest: " << mmu <<"\n";
        std::cout << "gameboy constructor called\n";
    }

void Gameboy::run() {
    tick();
}

void Gameboy::tick() {
    cpu->tick();
}