/*************************************************************************************************************************
*文件说明:
*        SIFT算法的实现
*开发环境:
*        Win10+VS2012+OpenCv2.4.8
*时间地点:
*        陕西师范大学.文津楼 2016.12.30
*再次修改时间:
*        陕西师范大学.文津楼 2017.2.24
*作者信息:
*        九月
**************************************************************************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <vector>
#include "sift.hpp"
 
 
using namespace std;
using namespace cv;
 
 
int main(int argc, char **argv)
{
	cv::Mat src = cv::imread("/data/1.jpg");
 
	if(src.empty())
	{
		cout << "jobs_512.jpg open error! "<<endl;
		getchar();
		return -1;
	}
 
	if(src.channels()!=3) return -2;
 
	vector<Keypoint> features;
 
	Sift(src, features, 1.6);                           //【1】SIFT特征点检测和特征点描述
 	DrawKeyPoints(src, features);                       //【2】画出关键点(特征点)
	DrawSiftFeatures(src, features);                    //【3】画出SIFT特征点
	write_features(features, "descriptor.txt");         //【4】将特征点写入文本
 
	cv::imshow("src", src);
	waitKey(0);
 
	return 0;
}


