#pragma once

#include "MatrixFilter.h"
#include "GrayscaleFilter.h"

class EdgeDetectionFilter : public MatrixFilters, GrayscaleFilter {
public:
    EdgeDetectionFilter();

    EdgeDetectionFilter(size_t threshold);

    void Apply(Image &img) const override;
private:
    size_t threshold_;
};