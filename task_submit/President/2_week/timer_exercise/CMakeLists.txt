cmake_minimum_required(VERSION 3.3)
project(test_timer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH /usr/share/pkgconfig)

find_package(PkgConfig REQUIRED)
pkg_search_module(OPENCV REQUIRED opencv)

add_library(Timer src/timer.cpp)
include_directories(${OPENCV_INCLUDE_DIRS} inc)
add_executable(test_timer test/main.cpp)
target_link_libraries(test_timer Timer ${OPENCV_LDFLAGS} pthread)
