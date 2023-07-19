#pragma once

#include "stdint.h"
#include <vector>
#include <string>
#include "Pixel.h"

using ColorsMap = std::vector<std::vector<Pixel>>;

class Image {
public:
    Image();

    Image(const ColorsMap& colorsMap, size_t height, size_t width);

    Image(const Image& other);

    size_t GetHeight() const;

    size_t GetWidth() const;

    const Pixel& GetPixel(size_t row, size_t column) const;

    void SetPixel(size_t row, size_t column, const Pixel& px);

    void SetSize(size_t new_height, size_t new_width);
private:
    size_t height_ = 0;
    size_t width_ = 0;
    ColorsMap data_;
};