#pragma once
#include "../cartridge/cartridge.h"

namespace memory {
    class Mmu {
        public:
            uint8_t rom0[16384];
            uint8_t rom1[16384];
            uint8_t vram[8192];
            uint8_t cart_ram[8192];
            uint8_t wram[8192];
            uint8_t oam[160];
            uint8_t io[128];
            uint8_t zp[128];

            std::shared_ptr<Cartridge> cartridge;
            Mmu(std::shared_ptr<Cartridge>&);
            uint8_t read(uint16_t);
            void write(uint16_t, uint8_t);
        private:
            bool bootRomActive() const;

            uint8_t readIo(const uint16_t) const;
            void writeIo(const uint16_t, uint8_t);

            bool inRange(uint16_t, int, int) const;
    };
}
