#include <iostream>
#include <vector>
#include "gameboy.h"

Gameboy::Gameboy(std::vector<uint8_t> cartridgeData) 
    :cartridge(getCartridge(std::move(cartridgeData)))
    {
        std::cout << "gameboy constructor called\n";
    
        video = std::make_shared<graphic::Video>(mmu, cpu);
        mmu = std::make_shared<memory::Mmu>(cartridge, video);
        cpu = std::make_unique<cpu::CPU>(mmu);
    }

void Gameboy::run() {
    tick();
}

void Gameboy::tick() {
    cpu->tick();
}