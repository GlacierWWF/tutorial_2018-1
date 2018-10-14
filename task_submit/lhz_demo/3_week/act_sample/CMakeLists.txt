

cmake_minimum_required(VERSION 3.10)

project(main)

find_package(PkgConfig REQUIRED)
pkg_search_module(OPENCV REQUIRED opencv)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${OpenCV_INCLUDE_DIRS})

AUX_SOURCE_DIRECTORY(src DIR_SRCS)
MESSAGE(STATUS “Src file: ${DIR_SRCS}”)

add_executable(main ${DIR_SRCS})

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(main -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
)

