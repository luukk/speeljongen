#include <iostream>
#include "../bitUtils.h"
#include "definitions.h"
#include "video.h"

namespace graphic {
    Video::Video(std::shared_ptr<memory::Mmu> &_mmu, std::unique_ptr<cpu::CPU> &_cpu) 
    : mmu(_mmu),
      cpu(std::move(_cpu))
    {
        std::cout << "video init\n";
    
    }

    ColorPallete Video::initializeColorPallete(uint8_t paletteByte) {
        std::cout << "initializeColorPallete\n";
        std::cout << unsigned(paletteByte) << "\n";

        uint8_t referencialColor0 = composeBits(bitValue(paletteByte, 1), bitValue(paletteByte, 0));
        uint8_t referencialColor1 = composeBits(bitValue(paletteByte, 3), bitValue(paletteByte, 2));
        uint8_t referencialColor2 = composeBits(bitValue(paletteByte, 5), bitValue(paletteByte, 4));
        uint8_t referencialColor3 = composeBits(bitValue(paletteByte, 7), bitValue(paletteByte, 6));

        Color actualColor0 =  getActualColor(referencialColor0);
        Color actualColor1 =  getActualColor(referencialColor1);
        Color actualColor2 =  getActualColor(referencialColor2);
        Color actualColor3 =  getActualColor(referencialColor3);

        colorPallete = { actualColor0, actualColor1, actualColor2, actualColor3};
    }

    Color Video::getActualColor(uint8_t pixelColor) const {
        switch (pixelColor) {
        case 0: return Color::white;
        case 1: return Color::lightGrey;
        case 2: return Color::darkGrey;
        case 3: return Color::black;
        default:
            std::cout << "Video::getActualColor: undefined color found!\n";
        }
    }
}