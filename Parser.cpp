#include "Parser.h"

Data::~Data() {
    for (size_t i = 0; i < filtersList.size(); ++i) {
        delete filtersList[i];
    }
}

void Parser::Parse(int argc, char** argv, Data& data) {
    if (argc < 3) {
        if (argc == 2 && argv[1] == help_command) {
            throw help_info;
        } else {
            throw invalid_number_params;
        }
    }

    data.input_path = argv[1];
    data.output_path = argv[2];

    for (size_t i = 3; i < static_cast<size_t>(argc);) {
        std::string filter_name = argv[i];
        if (filter_name == crop_name) {
            if (i + 2 >= static_cast<size_t>(argc)) {
                throw invalid_arg;
            }
            if (!isSize_tNumber(argv[i + 1]) || !isSize_tNumber(argv[i + 2])) {
                throw invalid_arg_type;
            }
            size_t width = atoi(argv[i + 1]);
            size_t height = atoi(argv[i + 2]);
            data.filtersList.push_back(new CropFilter(height, width));
            i += 3;
            continue;
        }
        if (filter_name == grayscale_name) {
            data.filtersList.push_back(new GrayscaleFilter);
            ++i;
            continue;
        }
        if (filter_name == negative_name) {
            data.filtersList.push_back(new NegativeFilter);
            ++i;
            continue;
        }
        if (filter_name == sharpening_name) {
            data.filtersList.push_back(new SharpeningFilter);
            ++i;
            continue;
        }
        if (filter_name == edge_detection_name) {
            if (i + 1 >= static_cast<size_t>(argc)) {
                throw invalid_arg;
            }
            if (!isSize_tNumber(argv[i + 1])) {
                throw invalid_arg_type;
            }
            int threshold = atoi(argv[i + 1]);
            data.filtersList.push_back(new EdgeDetectionFilter(threshold));
            i += 2;
            continue;
        }
        throw invalid_filter_name;
    }
}

bool Parser::isSize_tNumber(const std::string &path) {
    if (path.size() >= 18) {
        return false;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        if (!isdigit(path[i])) {
            return false;
        }
    }
    return true;
}
