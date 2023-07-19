#pragma once

#include "BaseFilter.h"

class NegativeFilter : public BaseFilter {
public:
    void Apply(Image &img) const override;
private:
    Pixel InvertColor(const Pixel& px) const;
};
