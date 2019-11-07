#pragma once
#include <vector>
#include "cpu/cpu.h"
#include "memory/mmu.h"
#include "cartridge/cartridge.h"

class Gameboy {
    public:
        Gameboy(std::vector<uint8_t>);
        void run();
    private:
        void tick();
        
        std::shared_ptr<Cartridge> cartridge;
        std::shared_ptr<memory::Mmu> mmu;
        std::unique_ptr<cpu::CPU> cpu;
};