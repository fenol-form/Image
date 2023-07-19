#pragma once

#include "Image.h"

class BaseFilter {
public:
    virtual void Apply(Image& img) const = 0;
    virtual ~BaseFilter() {
    };
};