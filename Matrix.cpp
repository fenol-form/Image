#include "Matrix.h"

Matrix::Matrix() {
}

Matrix::Matrix(const std::vector<std::vector<int>>& matrix) {
    matrix_ = matrix;
    size_ = matrix.size();
}

Pixel Matrix::GetChangedColor(const Image &img, size_t i, size_t j) const {
    int red = 0;
    int green = 0;
    int blue = 0;
    for (size_t y = 0; y < size_; ++y) {
        for (size_t x = 0; x < size_; ++x) {
            const auto& px = GetNearestPixel(img, i, j, y, x);
            red += px.red * matrix_[y][x];
            green += px.green * matrix_[y][x];
            blue += px.blue * matrix_[y][x];
        }
    }
    return Pixel(red, green, blue);
}

const Pixel& Matrix::GetNearestPixel(const Image &img, size_t i, size_t j, size_t y, size_t x) const {

    int64_t result_y = std::clamp(static_cast<int64_t>(i) + static_cast<int64_t>(y) - static_cast<int64_t>(size_ / 2),
                                  static_cast<int64_t>(0), static_cast<int64_t>(img.GetHeight() - 1));
    int64_t result_x = std::clamp(static_cast<int64_t>(j) + static_cast<int64_t>(x) - static_cast<int64_t>(size_ / 2),
                                  static_cast<int64_t>(0), static_cast<int64_t>(img.GetWidth() - 1));

    return img.GetPixel(result_y, result_x);
}