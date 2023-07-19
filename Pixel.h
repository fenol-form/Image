#pragma once

#include "stdint.h"
#include <algorithm>
#include <numeric>

struct Pixel {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    Pixel();

    bool operator ==(const Pixel& other) const;

    Pixel(uint8_t red, uint8_t green, uint8_t blue);
    Pixel(int red, int green, int blue);
};
