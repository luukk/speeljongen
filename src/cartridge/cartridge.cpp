#include <iostream>
#include "cartridge.h"


std::unique_ptr<CartridgeHeaderInformation> headerInformation(std::vector<uint8_t> rom) {
    std::unique_ptr<CartridgeHeaderInformation> info = std::make_unique<CartridgeHeaderInformation>();

    info->type = getCartridgeType(rom[header::cartridgeType]);
    info->romSize = getRomSize(rom[header::RomSize]);
    info->ramSize = getRamSize(rom[header::RamSize]);
    info->version = rom[header::RomVersion];

    std::cout << "cartridge header informantion: \n";
    std::cout << "  type: " << unsigned(rom[header::cartridgeType]) << "\n";
    std::cout << "  rom: " << unsigned(rom[header::RomSize]) << "\n";
    std::cout << "  ram: " << unsigned(rom[header::RamSize]) << "\n";
    std::cout << "  version: " << unsigned(rom[header::RomVersion]) << "\n";
    
    return info;
}

CartridgeType getCartridgeType(uint8_t cartridgeType) {
    switch (cartridgeType) {
    case 0x00:
    case 0x08:
    case 0x09:
        return CartridgeType::ROMOnly;
    
    /* Todo: now only supports rom only cartridge types.*/
    default:
        std::cout << "unrecognized cartridge type: " << unsigned(cartridgeType) << "\n";    
        return CartridgeType::Unknown;
    }
};

RomSize getRomSize(uint8_t romSize) {
    switch (romSize) {
    case 0x00:
        return RomSize::KB32;
    case 0x01:
        return RomSize::KB64;
    case 0x02:
        return RomSize::KB128;
    case 0x03:
        return RomSize::KB256;
    case 0x04:
        return RomSize::KB512;
    case 0x05:
        return RomSize::MB1;
    case 0x06:
        return RomSize::MB2;
    case 0x07:
        return RomSize::MB4;
    case 0x52:
        return RomSize::MB1P1;
    case 0x53:
        return RomSize::MB1p2;
    case 0x54:
        return RomSize::MB1P5;
    default:
        std::cout << "unrecognized rom size: " << unsigned(romSize) << "\n";
        return RomSize::KB32;
    }
}

RamSize getRamSize(uint8_t ramSize) {
    switch (ramSize)
    {
    case 0x00:
        return RamSize::None;
    case 0x01:
        return RamSize::KB2;
    case 0x02:
        return RamSize::KB8;
    case 0x03:
        return RamSize::KB32;
    case 0x04:
        return RamSize::KB64;
    case 0x05:
        return RamSize::KB128;
    default:
        std::cout << "unrecognized ram size: " << unsigned(ramSize) << "\n";
        return RamSize::None;
    }
}


Cartridge::Cartridge(std::vector<uint8_t> rom, std::shared_ptr<CartridgeHeaderInformation> headerInfo)
    : rom(std::move(rom)), cartridgeInformation(headerInfo)
    {
        
    }