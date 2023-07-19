#pragma once

#include <string>
#include <vector>
#include "CropFilter.h"
#include "NegativeFilter.h"
#include "GrayscaleFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"

struct Data {
    std::string input_path = "";
    std::string output_path = "";
    std::vector<BaseFilter* > filtersList;

    ~Data();
};

class Parser {
public:
    static void Parse(int argc, char** argv, Data& data);
private:
    inline const static std::string invalid_number_params = "invalid number of entered params\n"
                                                            "See 'image_processor --help'";
    inline const static std::string invalid_filter_name = "invalid filter's name\n"
                                                          "See 'image_processor --help'";
    inline const static std::string invalid_arg = "invalid number of filter's arguments\n"
                                                  "See 'image_processor --help'";
    inline const static std::string invalid_arg_type = "invalid type of filter's arguments\n"
                                                       "See 'image_processor --help'";

    inline const static std::string crop_name = "-crop";

    inline const static std::string grayscale_name = "-gs";

    inline const static std::string negative_name = "-neg";

    inline const static std::string sharpening_name = "-sharp";

    inline const static std::string edge_detection_name = "-edge";

    inline const static std::string help_command = "--help";

    inline const static std::string help_info = "image_processor help : \n\nthe first and second parameters are the path of your "
                                                "input and output file \n\nfilters : "
                                                "\n\n-crop width height \t crop according to given width and "
                                                "height on the left edge of image. \n"
                                                "-gs \t\t\t\t transform to a grayscale image\n"
                                                "-neg \t\t\t\t transform to a negative image\n"
                                                "-sharp \t\t\t\t increase image's sharpness\n"
                                                "-edge threshold\t\t edge detection";

    static bool isSize_tNumber(const std::string& path);
};