#pragma once
#include "../memory/mmu.h"
#include <memory>


namespace cpu {
    class Registers;
    class Flags;
    class Opcodes;

    extern std::unique_ptr<Registers> registerList;
    extern std::unique_ptr<Flags> flags;
    extern std::unique_ptr<Opcodes> opcodes;
    extern std::shared_ptr<memory::Mmu> mmu;
}