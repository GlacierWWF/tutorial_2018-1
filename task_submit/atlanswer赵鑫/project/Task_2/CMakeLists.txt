cmake_minimum_required(VERSION 3.12.3)
project(PX4OpticalFlow)

#Find OpenCV libraries
find_package(OpenCV REQUIRED)

#CXX standard is set to C++14
set(CMAKE_CXX_STANDARD 14)
add_definitions(-g -Wall)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#Set executable output location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

#Headers
include_directories(inc)
#Source files
aux_source_directory(src SOURCES)

add_executable(flow ${SOURCES})
#Link OpenCV libraries
target_link_libraries(flow ${OpenCV_LIBS})