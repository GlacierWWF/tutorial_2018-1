cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14")

project(sift)



add_executable(
	sift
	src/main.cpp
	src/SiftHelpers.h
	include/sift.cpp
	include/Sift.h
	include/sift.hpp
	include/sift.ipp
    include/CImg.h
)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(sift ${X11_LIBRARIES} -lpthread -lm)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)