#include <iostream>
#include "definitions.h"
#include "video.h"

namespace graphic {
    Video::Video(std::shared_ptr<memory::Mmu> &_mmu, std::unique_ptr<cpu::CPU> &_cpu) 
    : mmu(_mmu),
      cpu(std::move(_cpu))
    {
        std::cout << "video init\n";
    
    }

    ColorPallete Video::initializeColorPallete()
    {
        std::cout << "memes\n";
    }
}