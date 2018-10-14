cmake_minimum_required (VERSION 3.10.2)
project (DigitRecognize)

# set CXX standard as C++11
set (CMAKE_CXX_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find OpenCV libraries
find_package (OpenCV REQUIRED)

add_library (digit4 src/digit4_recognize.cpp)
include_directories (inc)

add_executable (DigitRecognize main/main.cpp)
# link libraries
target_link_libraries (DigitRecognize digit4 ${OpenCV_LIBS})
