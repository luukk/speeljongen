#include <iostream>
#include "gameboy.h"

Gameboy::Gameboy() :
    cpu(&mmu)
{
    std::cout << "gameboy constructor called\n";
}

void Gameboy::run() {
    tick();
}

void Gameboy::tick() {
    cpu.tick();
}