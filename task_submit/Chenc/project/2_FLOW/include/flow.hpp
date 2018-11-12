/*
*Title:main.cpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-11-9
*Version:1.0.0
*Abstract: A headflie include the function
*/
#ifndef FLOW_H
#define FLOW_H 
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
/*
class SAD
{
	public:
		SAD():winSize(7),DSR(30){}
		SAD(int _winSize,int _DSR):winSize(_winSize),DSR(_DSR){}
		Mat computerSAD(Mat &L,Mat &R); //计算SAD
	private:
		int winSize; //卷积核的尺寸
		int DSR;     //视差搜索范围
	
};
*/
double computerSAD(Mat &L,Mat &R,vector<Point>& point,vector<Point>& match_point);
double ABSDIFF(Mat &a,Mat &b);






#endif

