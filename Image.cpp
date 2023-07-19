#include "Image.h"

Image::Image() {
}

Image::Image(const ColorsMap &colorsMap, size_t height, size_t width) : height_(height), width_(width),
                                                                        data_(colorsMap) {
}

Image::Image(const Image &other) {
    (*this) = other;
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

const Pixel& Image::GetPixel(size_t row, size_t column) const {
    return data_[row][column];
}

void Image::SetPixel(size_t row, size_t column, const Pixel& px) {
    data_[row][column] = px;
}

void Image::SetSize(size_t new_height, size_t new_width) {
    height_ = std::min(new_height, height_);
    width_ = std::min(new_width, width_);
    data_.resize(height_);
    for (size_t i = 0; i < height_; ++i) {
        data_[i].resize(width_);
    }
}