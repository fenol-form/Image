#pragma once

#include "Image.h"
#include <algorithm>

class Matrix {
public:
    Matrix();

    Matrix(const std::vector<std::vector<int>>& matrix);

    Pixel GetChangedColor(const Image& img, size_t i, size_t j) const;
private:
    std::vector<std::vector<int>> matrix_ = {};
    size_t size_ = 0;

    const Pixel& GetNearestPixel(const Image& img, size_t i, size_t j, size_t y, size_t x) const;
};
