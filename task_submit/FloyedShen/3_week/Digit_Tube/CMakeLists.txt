#设置工程名称
PROJECT(Digit_Tube)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
#自己定制
SET(MY_TARGET Digit_Tube_PRO)
SET(MY_LINK Digit_Tube)


#设置CMAKE最小版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#设置编译器
SET(CMAKE_CXX_COMPILER "g++")
#设置构建类型，及相应的编译选项
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -march=native -O3 -pthread" )

#设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

MESSAGE("++++++++++++++Start Build+++++++++++++++++")

#当前目录的文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#添加子目录
ADD_SUBDIRECTORY(src)
#头文件搜索目录
INCLUDE_DIRECTORIES(inc)
#链接库搜索路径
LINK_DIRECTORIES(lib)
#设置链接库
#SET(EXTRA_LIBS ${EXTRA_LIBS} test1 test2)
SET(EXTRA_LIBS ${EXTRA_LIBS} ${MY_LINK})

#生成可执行文件
ADD_EXECUTABLE(${MY_TARGET} ${SRC_LIST})
#执行文件链接属性
TARGET_LINK_LIBRARIES(${MY_TARGET} ${EXTRA_LIBS})
target_link_libraries(Digit_Tube_PRO ${OpenCV_LIBS})