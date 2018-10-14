//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_14
//Version:v1.0.0
//Abstract:Read the number from pixel_cube.

#ifndef NIXIE_H
#define NIXIE_H

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
#pragma comment(lib,"opencv_world330.lib")

using namespace cv;
using namespace std;
using namespace std::chrono;


bool cmp(const Rect& a, const Rect& b);

bool White_noise(Mat image_mat);

//test if it is a LED tube
bool test_LED(Mat image_mat, int row_start, int row_end, int col_start, int col_end);

//calculate the proportion of white pixel
float white_proportion(Mat image_mat, int row_start, int row_end, int col_start, int col_end);

//test if the image is a numebr
int test_numebr(Mat image_mat);


#endif
