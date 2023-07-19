#include "BmpController.h"
#include "Image.h"
#include "Controller.h"
#include "Parser.h"
#include <iostream>

int main(int argc, char** argv) {
    Data data;
    try {
        Parser::Parse(argc, argv, data);
    } catch (std::string s) {
        std::cout << s << std::endl;
        return 0;
    }

    Image img;
    try {
        BmpController::GetImage(img, data.input_path);
    } catch(std::string s) {
        std::cout << s << std::endl;
        return 0;
    }

    ApplyFilters(img, data.filtersList);

    try {
        BmpController::Load(img, data.output_path);
    } catch(std::string s) {
        std::cout << s << std::endl;
    }
    return 0;
}