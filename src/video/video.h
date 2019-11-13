#pragma once

#include "definitions.h"
#include "../cpu/cpu.h"
#include "../cartridge/cartridge.h"
#include <memory>
#include <cstdint>


namespace graphic {
     class Video : public graphic::IVideo{
        public:
            Video(std::shared_ptr<memory::Mmu>&, std::unique_ptr<cpu::CPU>&);
            ~Video() = default;
            ColorPallete initializeColorPallete() override;
        private:
            uint8_t colorPallete;
            std::shared_ptr<memory::Mmu> mmu;
            std::unique_ptr<cpu::CPU> cpu;
    };  
}
