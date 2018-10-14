/***************************************** 
*tube2.hpp                 
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/14 
*
*Abustract: 定义部分函数
****************************************/ 
#ifndef TUBE2_H
#define TUBE2_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

void change(IplImage* src_img);

int movehighlight(IplImage* src,IplImage* dst );

#endif
