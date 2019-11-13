#pragma once

enum class Color {
        white,
        lightGrey,
        darkGrey,
        black
    };
    
struct ColorPallete {
    Color color0 = Color::white;
    Color color1 = Color::lightGrey;
    Color color2 = Color::darkGrey;
    Color color3 = Color::black;
};