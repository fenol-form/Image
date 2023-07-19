#pragma once

#include <string>
#include <vector>
#include "fstream"
#include "Image.h"

class BmpController {
public:
    static void GetImage(Image& img, const std::string& path);

    static void Load(const Image& img, const std::string& path);

private:
    using ColorsMap = std::vector<std::vector<Pixel>>;

    inline static const std::string message_exception_ = "failed open, invalid path";
    inline const static std::string invalid_file_extension_ = "invalid file extension";
    static const uint8_t fileHeaderSize_ = 14;
    static const uint8_t fileInfoSize_ = 40;
    static const uint8_t planes_ = 1;
    static const uint8_t bitPerPixel_ = 24;
    static const uint8_t firstWidthBit = 4;
    static const uint8_t lastWidthBit = 7;
    static const uint8_t firstHeightBit = 8;
    static const uint8_t lastHeightBit = 11;
};