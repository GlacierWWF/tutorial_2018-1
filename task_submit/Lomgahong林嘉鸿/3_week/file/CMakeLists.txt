cmake_minimum_required(VERSION 3.10.2)

project(Image_Recognition)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

add_library(numRec src/fun.cpp)

include_directories(inc)

add_executable(Image_Recognition main/main.cpp)

target_link_libraries(Image_Recognition numRec ${OpenCV_LIBS})
