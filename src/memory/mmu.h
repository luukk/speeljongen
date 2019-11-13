#pragma once
#include "../video/definitions.h"
#include "../cartridge/cartridge.h"

namespace graphic {
    /* TODO: refactor pure virtual interface */
    class IVideo {
    public:
        virtual ColorPallete initializeColorPallete(uint8_t) = 0;
        virtual ~IVideo() = default; // always always always needed with interfaces
    };
}

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
            std::shared_ptr<graphic::IVideo> video;
           
            Mmu(std::shared_ptr<Cartridge>&, std::shared_ptr<graphic::IVideo>&);
            ~Mmu() = default;

            uint8_t read(uint16_t);
            void write(uint16_t, uint8_t);
        private:
            bool bootRomActive() const;

            uint8_t readIo(const uint16_t) const;
            void writeIo(const uint16_t, uint8_t);

            bool inRange(uint16_t, int, int) const;
    };
}
