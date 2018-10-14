#ifndef IMAGERECIFY_H
#define IMAGERECIFY_H

#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define ERROR 1234

void ImageRecify(Mat src, Mat &dst);
double CalcDegree(const Mat &srcImage, Mat &dst);
void rotateImage(Mat src, Mat& img_rotate, double degree);
void moveImage(Mat src, Mat& img_moved, int x, int y);

#endif