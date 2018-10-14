#ifndef _PROGRAMME_H_
#define _PROGRAMME_H_

#include"opencv2/opencv.hpp"
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

/*
* @brief: 二值化
*/
void bin_pic(Mat &, int);

/*
* @brief: 把一张图片转化为0, 1向量
*/
void bin_vec(vector<vector<int> > &, Mat &, int);

/*
* @brief: 利用面积与中位数清除干扰轮廓
*/
void clean_rec(vector<vector<Point>> &);

/*
* @brief: 对轮廓进行排序
*/
vector<Rect> sort_rec(vector<vector<Point>> &);

/*
* @brief: 高斯滤波
*/
void gauss(Mat &);

/*
* @brief: 预处理, 进行光斑的粗糙滤除
*/
void pre_process(Mat &);

/*
* @brief: 找到轮廓长或宽的中位数
*/
int find_median(const vector<Rect>, int);

/*
* @brief: 把图片转化为统一尺寸
*/
void uniform_size(vector<Mat> &, vector<Mat> &);

/*
* @brief: 考虑轮廓是否进行旋转
*/
void if_rotate(vector<Mat> &, vector<Rect> &);

/*
* @brief: 大致的过程, 包括二值化, 膨胀, 旋转等
*/
void programme(int , char *[]);


#endif