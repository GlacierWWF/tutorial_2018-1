cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14")

project(identifier)

find_package(OpenCV REQUIRED)

add_executable(
	identifier
	src/main.cpp
	src/lineidentify.cpp
	include/lineidentify.hpp
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_link_libraries( identifier  ${OpenCV_LIBS} )
