#include "GrayscaleFilter.h"

void GrayscaleFilter::Apply(Image &img) const {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            uint8_t val = static_cast<uint8_t>(img.GetPixel(i, j).red * red_coef_) +
                          static_cast<uint8_t>(img.GetPixel(i, j).blue * blue_coef_) +
                          static_cast<uint8_t>(img.GetPixel(i, j).green * green_coef_);
            img.SetPixel(i, j, {val, val, val});
        }
    }
}