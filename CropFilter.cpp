#include "CropFilter.h"

CropFilter::CropFilter(size_t height, size_t width) : width_(width), height_(height) {
}

void CropFilter::Apply(Image &img) const {
    img.SetSize(height_, width_);
}