
#工程名字
PROJECT(Digit_recognition)

#规定cmake程序的最低版本
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )


set( SRC_LIST  main.cpp)

#生成可执行文件main
ADD_EXECUTABLE( main  ${SRC_LIST} )

# 寻找OpenCV库
FIND_PACKAGE( OpenCV REQUIRED )

# 添加头文件
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

# 链接OpenCV库
TARGET_LINK_LIBRARIES( main ${OpenCV_LIBS} )




