#include "Pixel.h"

Pixel::Pixel() {
}

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {
}

bool Pixel::operator==(const Pixel &other) const {
    return red == other.red && green == other.green && blue == other.blue;
}

Pixel::Pixel(int red, int green, int blue) {
    int min_color_value = static_cast<int>(std::numeric_limits<uint8_t>::min());
    int max_color_value = static_cast<int>(std::numeric_limits<uint8_t>::max());
    this->red = std::max(min_color_value, std::min(max_color_value, red));
    this->green = std::max(min_color_value, std::min(max_color_value, green));
    this->blue = std::max(min_color_value, std::min(max_color_value, blue));
}