cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor image_processor.cpp Image.cpp Pixel.cpp BmpController.cpp Controller.cpp
        Matrix.cpp MatrixFilter.cpp CropFilter.cpp GrayscaleFilter.cpp NegativeFilter.cpp SharpeningFilter.cpp
        EdgeDetectionFilter.cpp Parser.cpp)
