#pragma once

#include "BaseFilter.h"
#include "Matrix.h"

class MatrixFilters : virtual public BaseFilter {
public:
    MatrixFilters(const std::vector<std::vector<int>>& matrix);

    void Apply(Image &img) const override;
protected:
    Matrix filterMatrix_;
};
