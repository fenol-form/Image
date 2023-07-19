#include "Controller.h"

void ApplyFilters(Image &img, const std::vector<BaseFilter* >& filters) {
    for (const auto& filter : filters) {
        filter->Apply(img);
    }
}
