#include <iostream>
#include "mmu.h"
#include "bootRom.h"
#include "../cartridge/cartridge.h"

namespace memory {
    Mmu::Mmu(std::shared_ptr<Cartridge> &_cartridge, std::shared_ptr<graphic::IVideo> &_vid)
    :cartridge(_cartridge),
     video(_vid)
    {
        std::cout << "mmu init\n";
    }

    uint8_t Mmu::read(uint16_t address) {
        /* ROM */
        if(inRange(address, 0x00, 0x7FFF)) {
            if(inRange(address, 0x0, 0xFF)) {
                std::cout << "Mmu::read fetching boot rom opcode: " << unsigned(bootDMG[address]) << '\n';
                return bootDMG[address];
            }
            /*external */
            std::cout << "fetching opcode from cartridge: " << unsigned(address) << "\n";
            return cartridge->readByte(address);
        }

        /* VRAM */
        if(inRange(address, 0x8000, 0x9FFF)) {
        }

          /* External (cartridge) RAM */
        if (inRange(address, 0xA000, 0xBFFF)) {

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

    void Mmu::write(uint16_t address, uint8_t byte) {
             /* ROM */
        if(inRange(address, 0x00, 0x7FFF)) {
            
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
            writeIo(address, byte);
            return;
        }

        /* Interrupt Enable register */
        if(address == 0xFFFF) {
            //set interrupt 
        }
           
    }

    uint8_t Mmu::readIo(uint16_t address) const {

    } 

    void Mmu::writeIo(u_int16_t address, uint8_t byte) {
        switch(address) {
            /* TODO: audio channel 1: tone and sweep*/ 
            case 0xFF10:
            case 0xFF11:
            case 0xFF12:
            case 0xFF13:
            case 0xFF14:
                return;
            
            /* TODO: audio sound control register*/
            case 0xFF24:
                return;

            case 0xFF47: //LCD display enable
                std::cout << "initialize color palet";
                video->initializeColorPallete(byte);
                return;
        }
    }

    bool Mmu::bootRomActive() const {

    }

    bool Mmu::inRange(uint16_t address, int addressLow, int addressHigh ) const {
        return address >= addressLow && address <= addressHigh;
    }
}