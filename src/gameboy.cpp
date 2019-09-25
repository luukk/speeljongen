#include <iostream>
#include "gameboy.h"

Gameboy::Gameboy() :
    cpu(&mmu)
{
    std::cout << "gameboy constructor called";
}

void Gameboy::tick() {

}