#pragma once

#include "BaseFilter.h"

class GrayscaleFilter : virtual public BaseFilter {
public:
    void Apply(Image &img) const override;
private:
    const double red_coef_ = 0.299;
    const double blue_coef_ = 0.114;
    const double green_coef_ = 0.587;
};
