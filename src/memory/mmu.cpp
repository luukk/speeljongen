#include <iostream>
#include "mmu.h"
#include "bootRom.h"

namespace memory {
    uint8_t Mmu::read(uint16_t address) {
        /* ROM */
        if(inRange(address, 0x00, 0x7FFF)) {
            if(inRange(address, 0x0, 0xFF) && bootRomActive()) {
                std::cout << "fetching boot rom opcode: " << unsigned(bootDMG[address]) << '\n';
                return bootDMG[address];
            }
        }

        /* VRAM */
        if(inRange(address, 0x8000, 0x9FFF)) {

        }

        /* Internal work RAM */
        if(inRange(address, 0xC000, 0xDFFF)) {

        }

        /* Copy of working RAM */
        if(inRange(address, 0xE000, 0xDFFF)) {

        }

        /* OAM */
        if(inRange(address, 0xFE00, 0xFE9F)) {

        }

        /* UNUSABLE MEMORY */
        if(inRange(address, 0xFEA0, 0xFEFF)) {

        }

        /* Mapped IO */
        if(inRange(address, 0xFF00, 0xFF7F)) {

        }

        /* Interrupt Enable register */
        if(address == 0xFFFF) {
            //set interrupt 
        }
        
    }

    void Mmu::write(uint16_t address) {
         
    }

    uint8_t Mmu::readIo(uint16_t address) const {

    } 

    void Mmu::writeIo(u_int16_t address, uint8_t byte) {

    }

    bool Mmu::bootRomActive() const {

    }

    bool Mmu::inRange(uint16_t address, int addressLow, int addressHigh ) const {
        return address >= addressLow && address <= addressHigh;
    }
}