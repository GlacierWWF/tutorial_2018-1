# Timer 使用方法

作者：张灏桓

修订：张灏桓

日期：2018-10-6

版本：1.0.0

摘要：基于OPENCV3的多线程简易计时工具Timer的使用方法

## 1.依赖库

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <ratio>
#include <pthread.h>
#include <opencv2/opencv.hpp>

## 2.编译方法

mkdir build

cp 1.png build/

cd build

cmake ..

make

## 3.运行方式

cd build

./timer