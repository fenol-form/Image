#pragma once

#include "BaseFilter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(size_t height, size_t width);

    void Apply(Image &img) const override;
private:
    size_t width_;
    size_t height_;
};