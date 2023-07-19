#pragma once

#include "Image.h"
#include "BaseFilter.h"

void ApplyFilters(Image& img, const std::vector<BaseFilter*>& filters);