cmake_minimum_required(VERSION 3.0)
PROJECT(LEDdetect)
add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
#SET(SRC_LIST LEDdetect.cpp)
#MESSAGE(STATUS "This is BINARY dir" ${LEDdetect_BINARY_DIR})
ADD_EXECUTABLE(
LEDdetect
src/LEDdetect.cpp
src/Process.cpp
src/Degree.cpp
include/Process.hpp
include/Degree.hpp
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(LEDdetect ${OpenCV_LIBS})
