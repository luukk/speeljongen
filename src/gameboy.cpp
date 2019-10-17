#include <iostream>
#include <vector>
#include "gameboy.h"
#include "cartridge/cartridge.h"
// #include 

Gameboy::Gameboy(std::vector<uint8_t> cartridgeData):
    cartridge(cartridgeData, headerInformation(cartridgeData)),
    cpu(&mmu)
{
    // std::cout << &info;
    std::cout << "gameboy constructor called\n";
}

void Gameboy::run() {
    tick();
}

void Gameboy::tick() {
    cpu.tick();
}