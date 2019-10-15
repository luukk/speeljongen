#include <iostream>
#include "cartridge.h"


std::unique_ptr<CartridgeHeaderInformation> headerInformation(std::vector<uint8_t> rom) {
    std::unique_ptr<CartridgeHeaderInformation> info;

    uint8_t cartridgeType = rom[header::cartridgeType];


    // info->type = 

    std::cout << "header informantion\n";
    std::cout << unsigned(rom[326]);
    return 0;
}

Cartridge::Cartridge(std::unique_ptr<CartridgeHeaderInformation> inf) {
    std::cout << "cartridge initialed\n";
}