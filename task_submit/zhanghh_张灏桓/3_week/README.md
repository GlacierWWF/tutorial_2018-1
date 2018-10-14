# 使用方法

作者：张灏桓

修订：张灏桓

日期：2018-10-14

版本：1.0.0

摘要：基于OPENCV3的数码管识别程序的使用方法

## 1.依赖库

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <ratio>
#include <pthread.h>
#include <math.h>
#include <cstdlib>
#include<opencv2/opencv.hpp>

## 2.编译方法

cd build

cmake ..

make

## 3.运行方式

cd build

./Nixie_tube 

#### 输入样例1：

./sim_sample1.jpg

#### 输入样例2：

./hard_sample1_1.jpg ./hard_sample1_2.jpg