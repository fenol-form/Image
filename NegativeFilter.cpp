#include "NegativeFilter.h"

void NegativeFilter::Apply(Image &img) const {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            img.SetPixel(i, j, InvertColor(img.GetPixel(i, j)));
        }
    }
}

Pixel NegativeFilter::InvertColor(const Pixel &px) const {
    Pixel result;
    uint8_t max_color_value = std::numeric_limits<uint8_t>::max();
    result.red = max_color_value - px.red;
    result.green = max_color_value - px.green;
    result.blue = max_color_value - px.blue;
    return result;
}