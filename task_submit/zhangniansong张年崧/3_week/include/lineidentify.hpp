#ifndef LINEIDENTIFY_H
#define LINEIDENTIFY_H

#include <opencv2/opencv.hpp> 
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


bool IsAllWhite(Mat inputmat);
bool IsAllBlack(Mat inputmat);
bool Iswhite(Mat inputmat, int row_start, int row_end, int col_start, int col_end);

#endif