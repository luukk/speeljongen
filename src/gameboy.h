#pragma once
#include "cpu/cpu.h"
#include "memory/mmu.h"


class Gameboy {
    public:
        Gameboy();
        void run();
    private:
        void tick();

        cpu::CPU cpu;
        memory::Mmu mmu;
};