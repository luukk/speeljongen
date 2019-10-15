#pragma once

#include <string>
#include <memory>
#include <vector>
#include <cstdint>

namespace header { 
    const int startVector = 0x100;
    const int nintendoLogo = 0x104;
    const int gameTitle = 0x134;
    const int manufacturerCode = 0x13F;
    const int GBCFlag = 0x143;
    const int newLicenceCode = 0x144;
    const int SGBFlag = 0x146;
    const int cartridgeType = 0x147;
    const int RomSize = 0x148;
    const int RamSize = 0x149;
    const int destinationCode = 0x14A;
    const int oldLicenseCode = 0x14B;
    const int RomVersion = 0x14C;
    const int headerChecksum = 0x14D;
    const int globalChecksum = 0x14E;
};

enum class CartridgeType {
    ROMOnly,
    MBC1,
    MBC2,
    MBC3,
    MBC4,
    MBC5,
    Unknown
};

CartridgeType getCartridgeType(uint8_t);

enum class RomSize {
    KB32,
    KB64,
    KB128,
    KB256,
    KB512,
    MB1,
    MB2,
    MB4,
    MB1P1,
    MB1p2,
    MB1P5
};

RomSize getRomSize(uint8_t);

enum class RamSize {
    None,
    KB2,
    KB8,
    KB32,
    KB128,
    KB64
};

RamSize getRamSize(uint8_t);

class CartridgeHeaderInformation { 
    public:
        CartridgeType type;
        RomSize romSize;
        RamSize ramSize;
        uint8_t version;

        uint16_t headerChecksum;
        uint16_t globalChecksum;
};

extern std::unique_ptr<CartridgeHeaderInformation> headerInformation(std::vector<uint8_t>);

class Cartridge {
public:
    Cartridge(
        std::unique_ptr<CartridgeHeaderInformation> cartridge_info
    );
};