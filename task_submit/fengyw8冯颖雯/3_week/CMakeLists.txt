#规定cmake程序的最低版本
cmake_minimum_required( VERSION 2.6 )

#工程名字
project(DigitRecognization)

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

set( SRC_LIST  DigitRecognization.cpp)

#生成可执行文件main
add_executable(src/main.cpp
	       include/utility.h)

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

# 添加头文件
link_directories( ${OpenCV_INCLUDE_DIRS} )

# 链接OpenCV库
target_link_libraries( DigitRecognization ${OpenCV_LIBS} )



