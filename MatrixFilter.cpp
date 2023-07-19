#include "MatrixFilter.h"

MatrixFilters::MatrixFilters(const std::vector<std::vector<int>> &matrix) {
    filterMatrix_ = Matrix(matrix);
}

void MatrixFilters::Apply(Image &img) const {
    Image tmp_image(img);
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            img.SetPixel(i, j, filterMatrix_.GetChangedColor(tmp_image, i, j));
        }
    }
}