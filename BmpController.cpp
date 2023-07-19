#include "BmpController.h"

void BmpController::GetImage(Image &img, const std::string &path) {
    std::ifstream input_file;
    input_file.open(path, std::ios::in | std::ios_base::binary);

    if (!input_file.is_open()) {
        throw message_exception_;
    }

    unsigned char file_header[fileHeaderSize_] = {0};
    unsigned char info_header[fileInfoSize_] = {0};


    input_file.read(reinterpret_cast<char*>(file_header), fileHeaderSize_);
    input_file.read(reinterpret_cast<char*>(info_header), fileInfoSize_);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw invalid_file_extension_;
    }

    size_t width = 0, height = 0;
    for (size_t i = firstWidthBit; i <= lastWidthBit; ++i) {
        width += (info_header[i] << (i - firstWidthBit) * 8);
    }
    for (size_t i = firstHeightBit; i <= lastHeightBit; ++i) {
        height += (info_header[i] << (i - firstHeightBit) * 8);
    }

    ColorsMap colorsMap(height, std::vector<Pixel>(width));

    const char padding = ((4 - (width * 3) % 4) % 4);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            char colors[3];
            input_file.read(colors, 3);
            colorsMap[i][j].blue = colors[0];
            colorsMap[i][j].green = colors[1];
            colorsMap[i][j].red = colors[2];
        }
        input_file.ignore(padding);
    }

    for (size_t i = 0; i < height / 2; ++i) {
        std::swap(colorsMap[i], colorsMap[height - i - 1]);
    }

    img = Image(colorsMap, height, width);

    input_file.close();
}

void BmpController::Load(const Image &img, const std::string &path) {
    std::ofstream output_file;
    output_file.open(path, std::ios::out | std::ios_base::binary);

    if (!output_file.is_open()) {
        throw message_exception_;
    }

    const char padding = ((4 - (img.GetWidth() * 3) % 4) % 4);
    const size_t file_size = img.GetWidth() * img.GetHeight() * 3 + padding * img.GetWidth() + fileInfoSize_
                             + fileHeaderSize_;
    unsigned char file_header[fileHeaderSize_] = {0};
    unsigned char info_header[fileInfoSize_] = {0};

    // file_header :
    file_header[0] = 'B';
    file_header[1] = 'M';

    for (size_t i = 2; i <= 5; ++i) {
        file_header[i] = file_size >> ((i - 2) * 8);
    }

    file_header[10] = fileHeaderSize_ + fileInfoSize_;

    // info_header :
    info_header[0] = fileInfoSize_;

    for (size_t i = firstWidthBit; i <= lastWidthBit; ++i) {
        info_header[i] = (img.GetWidth() >> ((i - firstWidthBit) * 8));
    }
    for (size_t i = firstHeightBit; i <= lastHeightBit; ++i) {
        info_header[i] = (img.GetHeight() >> ((i - firstHeightBit) * 8));
    }

    info_header[12] = planes_;

    info_header[14] = bitPerPixel_;

    output_file.write(reinterpret_cast<char*>(file_header), fileHeaderSize_);
    output_file.write(reinterpret_cast<char*>(info_header), fileInfoSize_);

    for (size_t i = img.GetHeight() - 1; i < SIZE_MAX; --i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            char colors[3] = {static_cast<char>(img.GetPixel(i, j).blue), static_cast<char>(img.GetPixel(i, j).green),
                              static_cast<char>(img.GetPixel(i, j).red)};
            output_file.write(colors, 3);
        }
        char zeros[3] = {0, 0, 0};
        output_file.write(zeros, padding);
    }

    output_file.close();
}
