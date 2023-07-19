#include "EdgeDetectionFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter() : MatrixFilters({{0,  -1, 0},
                                                            {-1, 4,  -1},
                                                            {0,  -1, 0}}) {
}

EdgeDetectionFilter::EdgeDetectionFilter(size_t threshold) : EdgeDetectionFilter() {
    threshold_ = threshold;
}

void EdgeDetectionFilter::Apply(Image &img) const {
    Image tmp_image(img);
    GrayscaleFilter::Apply(img);
    MatrixFilters::Apply(img);
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            if (img.GetPixel(i, j).green > threshold_) {
                uint8_t max_color = std::numeric_limits<uint8_t>::max();
                img.SetPixel(i, j, Pixel(max_color, max_color, max_color));
            } else {
                uint8_t min_color = std::numeric_limits<uint8_t>::min();
                img.SetPixel(i, j, Pixel(min_color, min_color, min_color));
            }
        }
    }
}
