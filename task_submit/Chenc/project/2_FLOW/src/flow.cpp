/*
*Title:main.cpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-11-9
*Version:1.0.0
*Abstract: A program to realize SAD matching and return 
*/
#include<iostream>
#include<opencv2/opencv.hpp>
#include"flow.hpp"
using namespace std;
using namespace cv;
double computerSAD(Mat &L,Mat &R,vector<Point>& point,vector<Point>& match_point)
// input:pre picture,nex picture,keypoint;
// output:average of pixel displacemet
{
	double output;
	int winSize = 4;// convelutional kenerl
	int DSR;  // 
	int Height=L.rows;
	int Width=L.cols;
	int k = 0;
	double diff;
	int x_min = 0,y_min = 0;
	DSR = (Width/winSize-1) * (Height/winSize-1);
	//int hist[DSR+1];
	double dist = 0.0;

	//use two kernel to realize the matching 
	//left kernel:kernel from keypoints of input image
	//right kernel:traverse the second image to find the best matching point
	Mat Kernel_L(Size(winSize,winSize),CV_8U,Scalar::all(0));
	Mat Kernel_R(Size(winSize,winSize),CV_8U,Scalar::all(0));
	for(int i=0;i<point.size();i++)
	{	
		int temp = 10000;
		int x = point[i].x;
		int y = point[i].y;
		Kernel_L=L(Rect(x,y,winSize,winSize));//left image
		for(int p=1 ;p < Width-winSize-1;p+=winSize-1)
		{
			for(int q=1;q < Height-winSize-1;q+=winSize-1)	
				{
					Kernel_R=R(Rect(p,q,winSize,winSize));
		        	diff = ABSDIFF(Kernel_L, Kernel_R);//SAD matching
					//cout<<"diff_now is"<<diff<<endl;
					if(diff < temp)
					{
						x_min = p;  //best match block in image2
						y_min = q;
						temp = diff;
					}
				}
		}
		
		//x_min,y_min is the best match point in image2 which detected
		match_point[i].x = x_min;
		match_point[i].y = y_min;
		//cout<<"******************************************"<<endl;
		//cout<<"the coordinate of x1,y1 is "<<"("<<point[i].x<<" , "<<point[i].y<<")"<<endl;
		//cout<<"the coordinate of x2,y2 is "<<"("<<match_point[i].x<<" , "<<match_point[i].y<<")"<<endl;
		//cout<<"******************************************"<<endl;
		
		double temp1 = x - x_min;
		double temp2 = y - y_min;
		
		dist = double(abs(temp1) + abs(temp2));
		output = dist;
		
	}
	return output;
}


//calculate the diffrence of two 4x4 pixel blocks
double ABSDIFF(Mat &a,Mat &b)
{
	double sum = 0.0;
	int temp;
	for(int j=0;j<a.rows;j++)
	{
		uchar* a_data = a.ptr<uchar>(j);
		uchar* b_data = b.ptr<uchar>(j);
		for(int i=0;i<a.cols;i++)
		{
			temp = a_data[i] - b_data[i];
			sum = sum + pow(temp,2);
			
		}
	}
	return sqrt(sum);
}
