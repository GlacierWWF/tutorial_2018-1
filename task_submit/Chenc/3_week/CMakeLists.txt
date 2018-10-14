cmake_minimum_required(VERSION 3.0)
PROJECT(LEDdetect)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
find_package(OpenCV REQUIRED)
#SET(SRC_LIST LEDdetect.cpp)
#MESSAGE(STATUS "This is BINARY dir" ${LEDdetect_BINARY_DIR})
ADD_EXECUTABLE(
detect
src/LEDdetect.cpp
)
link_directories(${CMAKE_BINARY_DIR}/bin)
target_link_libraries(detect ${OpenCV_LIBS})
