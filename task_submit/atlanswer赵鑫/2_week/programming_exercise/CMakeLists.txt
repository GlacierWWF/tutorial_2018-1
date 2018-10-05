cmake_minimum_required(VERSION 3.2.2)
project(IPNetwork)

#Set CPP standard
set(CMAKE_CXX_STANDARD 14)

#Set headers
#include(*.hpp)

#Set sources
file(GLOB SOURCES "*.cpp")

#Executable
add_executable(IPNetwork ${SOURCES})