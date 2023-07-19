#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch/catch.hpp"

#include "BmpController.h"
#include "Image.h"
#include "Pixel.h"
#include "BaseFilter.h"
#include "MatrixFilter.h"
#include "CropFilter.h"
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "Controller.h"

TEST_CASE("BmpController") {
    Image img;
    try {
        BmpController::GetImage(img, "./all_gray.bmp");
        throw "impossible exception";
    } catch (const std::string &exception) {
        REQUIRE(exception == "failed open");
    }

    BmpController::GetImage(img, "../examples/all_gray.bmp");

    REQUIRE(img.GetHeight() == 2);
    REQUIRE(img.GetWidth() == 8);

    std::vector<Pixel> expected_colors(8);
    for (size_t i = 0; i < 8; ++i) {
        expected_colors[i] = img.GetPixel(0, i);
    }

    try {
        BmpController::Load(img, "../output/all_gray_result.bmp");
        throw "impossible exception";
    } catch (const std::string &exception) {
        REQUIRE(exception == "failed open");
    }

    BmpController::Load(img, "../outputs/all_gray_result.bmp");
    BmpController::GetImage(img, "../outputs/all_gray_result.bmp");

    for (size_t i = 0; i < 8; ++i) {
        REQUIRE(expected_colors[i] == img.GetPixel(0, i));
    }
}

TEST_CASE("CropFilter") {
    Image img;
    BmpController::GetImage(img, "../examples/blackbuck.bmp");

    CropFilter cropf(400, 300);
    std::vector<BaseFilter*> filters;
    filters.push_back(&cropf);

    std::vector<Pixel> lastColors;
    size_t range = 10;
    for (size_t i = 0; i < range; ++i) {
        lastColors.push_back(img.GetPixel(0, i));
    }

    ApplyFilters(img, filters);

    BmpController::Load(img, "../outputs/crop_result.bmp");

    BmpController::GetImage(img, "../outputs/crop_result.bmp");

    REQUIRE(img.GetWidth() == 300);
    REQUIRE(img.GetHeight() == 400);
    for (size_t i = 0; i < range; ++i) {
        REQUIRE(lastColors[i] == img.GetPixel(0, i));
    }

    cropf = CropFilter(10000, 10000);
    filters = {&cropf};
    ApplyFilters(img, filters);

    REQUIRE(img.GetWidth() == 300);
    REQUIRE(img.GetHeight() == 400);
}

TEST_CASE("NegativeFilter") {
    Image img;
    BmpController::GetImage(img, "../examples/blackbuck.bmp");

    NegativeFilter neg;
    std::vector<BaseFilter*> filters;
    filters.push_back(&neg);

    std::vector<Pixel> lastColors;
    size_t range = 10;
    for (size_t i = 0; i < range; ++i) {
        lastColors.push_back(img.GetPixel(0, i));
    }
    size_t lastWidth = img.GetWidth();
    size_t lastHeight = img.GetHeight();

    ApplyFilters(img, filters);

    BmpController::Load(img, "../outputs/negative_result.bmp");

    BmpController::GetImage(img, "../outputs/negative_result.bmp");

    REQUIRE(lastWidth == img.GetWidth());
    REQUIRE(lastHeight == img.GetHeight());

    for (size_t i = 0; i < range; ++i) {
        REQUIRE(lastColors[i].green == std::numeric_limits<uint8_t>::max() - img.GetPixel(0, i).green);
        REQUIRE(lastColors[i].blue == std::numeric_limits<uint8_t>::max() - img.GetPixel(0, i).blue);
        REQUIRE(lastColors[i].red == std::numeric_limits<uint8_t>::max() - img.GetPixel(0, i).red);
    }

}

TEST_CASE("GrayscaleFilter") {
    Image img;
    BmpController::GetImage(img, "../examples/example.bmp");

    GrayscaleFilter gs;
    std::vector<BaseFilter*> filters;
    filters.push_back(&gs);

    std::vector<Pixel> lastColors;
    size_t range = 10;
    for (size_t i = 0; i < range; ++i) {
        lastColors.push_back(img.GetPixel(0, i));
    }
    size_t lastWidth = img.GetWidth();
    size_t lastHeight = img.GetHeight();


    ApplyFilters(img, filters);

    BmpController::Load(img, "../outputs/grayscale_result.bmp");

    BmpController::GetImage(img, "../outputs/grayscale_result.bmp");

    REQUIRE(lastWidth == img.GetWidth());
    REQUIRE(lastHeight == img.GetHeight());

    for (size_t i = 0; i < range; ++i) {
        Pixel px = img.GetPixel(i, 0);
        REQUIRE(px.green == px.blue);
        REQUIRE(px.green == px.red);
        REQUIRE(px.red == px.blue);
    }
}

TEST_CASE("Matrix corner pixels") {
    Image img;
    BmpController::GetImage(img, "../examples/spirals.bmp");

    Matrix m({{1, 1, 0},
              {1, 0, 0},
              {0, 0, 0}});

    Pixel old_px = img.GetPixel(0, 0);
    Pixel new_px = m.GetChangedColor(img, 0, 0);

    REQUIRE(new_px.green == std::min(255, 3 * static_cast<int>(old_px.green)));
    REQUIRE(new_px.blue == std::min(255, 3 * static_cast<int>(old_px.blue)));
    REQUIRE(new_px.red == std::min(255, 3 * static_cast<int>(old_px.red)));

    m = Matrix({{0, 1, 1},
                {0, 0, 1},
                {0, 0, 0}});

    old_px = img.GetPixel(0, img.GetWidth() - 1);
    new_px = m.GetChangedColor(img, 0, img.GetWidth() - 1);

    REQUIRE(new_px.green == std::min(255, 3 * static_cast<int>(old_px.green)));
    REQUIRE(new_px.blue == std::min(255, 3 * static_cast<int>(old_px.blue)));
    REQUIRE(new_px.red == std::min(255, 3 * static_cast<int>(old_px.red)));


    m = Matrix({{0, 0, 0},
                {0, 0, 1},
                {0, 1, 1}});

    old_px = img.GetPixel(img.GetHeight() - 1, img.GetWidth() - 1);
    new_px = m.GetChangedColor(img, img.GetHeight() - 1, img.GetWidth() - 1);

    REQUIRE(new_px.green == std::min(255, 3 * static_cast<int>(old_px.green)));
    REQUIRE(new_px.blue == std::min(255, 3 * static_cast<int>(old_px.blue)));
    REQUIRE(new_px.red == std::min(255, 3 * static_cast<int>(old_px.red)));


    m = Matrix({{0, 0, 0},
                {1, 0, 0},
                {1, 1, 0}});

    old_px = img.GetPixel(img.GetHeight() - 1, 0);
    new_px = m.GetChangedColor(img, img.GetHeight() - 1, 0);

    REQUIRE(new_px.green == std::min(255, 3 * static_cast<int>(old_px.green)));
    REQUIRE(new_px.blue == std::min(255, 3 * static_cast<int>(old_px.blue)));
    REQUIRE(new_px.red == std::min(255, 3 * static_cast<int>(old_px.red)));

}

TEST_CASE("Matrix other pixels") {
    Image img;
    BmpController::GetImage(img, "../examples/spirals.bmp");

    Matrix m({{1, -1, 1},
              {0, 0, 0},
              {0, 0, 0}});

    size_t wd = img.GetWidth();
    size_t hg = img.GetHeight();
    Pixel new_px = m.GetChangedColor(img, 0, wd / 2);

    Pixel ex_px = Pixel(-static_cast<int>(img.GetPixel(0, wd / 2).red) +
                        static_cast<int>(img.GetPixel(0, wd / 2 - 1).red) +
                        static_cast<int>(img.GetPixel(0, wd / 2 + 1).red),
                        -static_cast<int>(img.GetPixel(0, wd / 2).green) +
                        static_cast<int>(img.GetPixel(0, wd / 2 - 1).green) +
                        static_cast<int>(img.GetPixel(0, wd / 2 + 1).green),
                        -static_cast<int>(img.GetPixel(0, wd / 2).blue) +
                        static_cast<int>(img.GetPixel(0, wd / 2 - 1).blue) +
                        static_cast<int>(img.GetPixel(0, wd / 2 + 1).blue));

    REQUIRE(ex_px == new_px);


    m = Matrix({{1, 0, 0},
              {-1, 0, 0},
              {1, 0, 0}});

    new_px = m.GetChangedColor(img, hg / 2, 0);

    ex_px = Pixel(-static_cast<int>(img.GetPixel(hg / 2, 0).red) +
                        static_cast<int>(img.GetPixel(hg / 2 - 1, 0).red) +
                        static_cast<int>(img.GetPixel(hg / 2 + 1, 0).red),
                        -static_cast<int>(img.GetPixel(hg / 2, 0).green) +
                        static_cast<int>(img.GetPixel(hg / 2 - 1, 0).green) +
                        static_cast<int>(img.GetPixel(hg / 2 + 1, 0).green),
                        -static_cast<int>(img.GetPixel(hg / 2, 0).blue) +
                        static_cast<int>(img.GetPixel(hg / 2 - 1, 0).blue) +
                        static_cast<int>(img.GetPixel(hg / 2 + 1, 0).blue));

    REQUIRE(ex_px == new_px);


    m = Matrix({{0, 0, 0},
                {0, 0, 0},
                {1, -1, 1}});

    new_px = m.GetChangedColor(img, hg - 1, wd / 2);

    ex_px = Pixel(-static_cast<int>(img.GetPixel(hg - 1, wd / 2).red) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 - 1).red) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 + 1).red),
                  -static_cast<int>(img.GetPixel(hg - 1, wd / 2).green) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 - 1).green) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 + 1).green),
                  -static_cast<int>(img.GetPixel(hg - 1, wd / 2).blue) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 - 1).blue) +
                  static_cast<int>(img.GetPixel(hg - 1, wd / 2 + 1).blue));

    REQUIRE(ex_px == new_px);


    m = Matrix({{0, 0, 1},
                {0, 0, -1},
                {0, 0, 1}});

    new_px = m.GetChangedColor(img, hg / 2, wd - 1);

    ex_px = Pixel(-static_cast<int>(img.GetPixel(hg / 2, wd - 1).red) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd - 1).red) +
                  static_cast<int>(img.GetPixel(hg / 2 + 1, wd - 1).red),
                  -static_cast<int>(img.GetPixel(hg / 2, wd - 1).green) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd - 1).green) +
                  static_cast<int>(img.GetPixel(hg / 2 + 1, wd - 1).green),
                  -static_cast<int>(img.GetPixel(hg / 2, wd - 1).blue) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd - 1).blue) +
                  static_cast<int>(img.GetPixel(hg / 2 + 1, wd - 1).blue));

    REQUIRE(ex_px == new_px);


    m = Matrix({{0, 1, 0},
                {3, 0, 0},
                {0, 0, -2}});

    new_px = m.GetChangedColor(img, hg / 2, wd / 2);

    ex_px = Pixel(3 * static_cast<int>(img.GetPixel(hg / 2, wd / 2 - 1).red) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd / 2).red) -
                  2 * static_cast<int>(img.GetPixel(hg / 2 + 1, wd / 2 + 1).red),
                  3 * static_cast<int>(img.GetPixel(hg / 2, wd / 2 - 1).green) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd / 2).green) -
                  2 * static_cast<int>(img.GetPixel(hg / 2 + 1, wd / 2 + 1).green),
                  3 * static_cast<int>(img.GetPixel(hg / 2, wd / 2 - 1).blue) +
                  static_cast<int>(img.GetPixel(hg / 2 - 1, wd / 2).blue) -
                  2 * static_cast<int>(img.GetPixel(hg / 2 + 1, wd / 2 + 1).blue));

    REQUIRE(ex_px == new_px);
}

TEST_CASE("EdgeDetectionFilter") {
    Image img;
    BmpController::GetImage(img, "../examples/spirals.bmp");

    EdgeDetectionFilter edg(20);
    std::vector<BaseFilter*> filters;
    filters.push_back(&edg);

    size_t lastWidth = img.GetWidth();
    size_t lastHeight = img.GetHeight();

    ApplyFilters(img, filters);

    BmpController::Load(img, "../outputs/edge_detection_result.bmp");

    BmpController::GetImage(img, "../outputs/edge_detection_result.bmp");

    REQUIRE(lastWidth == img.GetWidth());
    REQUIRE(lastHeight == img.GetHeight());

    size_t range = 10;
    for (size_t i = 0; i < range; ++i) {
        REQUIRE((img.GetPixel(0, i).green == 255 || img.GetPixel(0, i).green == 0));
        REQUIRE((img.GetPixel(0, i).green == img.GetPixel(0, i).red &&
                img.GetPixel(0, i).green == img.GetPixel(0, i).blue));
    }
}










