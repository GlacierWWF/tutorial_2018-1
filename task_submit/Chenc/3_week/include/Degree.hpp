#ifndef DEGREE_H
#define DEGREE_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Degree.hpp"

using namespace cv;
using namespace std;
//度数转换
double DegreeTrans(double theta);
//逆时针旋转图像degree角度（原尺寸）    
void rotateImage(Mat src, Mat& img_rotate, double degree);
//通过霍夫变换计算角度
double CalcDegree(const Mat &srcImage, Mat &dst);
void ImageRecify(Mat src, Mat& resulyImage);
#endif
