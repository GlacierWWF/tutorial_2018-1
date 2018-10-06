/*****************************************************************
 * @file	Timer.cpp
 * @brief	This file define the member function of class Timer
 * Details.
 *
 * @Author	Lomgahong
 * @email	1073097404@qq.com
 * @version	1.0.1
 * ---------------------------------------------------------------
 * Change History:
 *    <Date>  |<Version>|<Author> |<Description>
 * 2018/10/07 |  1.0.1  |Lomgahong|Create file
 *---------------------------------------------------------------
 *
 * **************************************************************/


#include"Timer.hpp"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<chrono>

using namespace std;
using namespace cv;

/**
 * 构造函数
 */
Timer::Timer()
{
	image=cv::imread("Image");
}

/**
 * 用于保持计时和输出的函数
 */
void Timer::countTime()
{
	//justnow为当前时间点
 	std::chrono::steady_clock::time_point justnow;
	justnow=chrono::steady_clock::now();
	//time_b为两个时间点之间的时间长度
	std::chrono::milliseconds time_b;
	//用duration_cast进行类型转换
	time_b=chrono::duration_cast<chrono::milliseconds>(justnow-end_time);
	//不断输出刷新字符串
	stringstream output_stream;
	output_stream<<"Time:"<<time_b.count()<<"ms";
	string output_string;
	output_string=output_stream.str();
	//确定字符串的方位
	cv::Point xy;
	xy.x=0;
	xy.y=512;
	//输出
	cv::putText(image,output_string,xy,FONT_HERSHEY_DUPLEX,4,Scalar(255),4,false);
	cv::imshow("Timer",image);
	image=cv::imread("Image.png");
	cv::waitKey(1);
}
		
/**
 * 用于打开窗口的函数
 */
void Timer::open()
{
	//定义图片的地址参数
	image=cv::imread("Image.png");
	cv::namedWindow("Timer",512);
	cv::imshow("Timer",image);
	cv::waitKey(1);
}

/**
 * 用于关闭窗口的函数
 */
void Timer::close()
{
	cv::destroyWindow("Timer");
}

/**
 * 用于开始计时的函数
 */
void Timer::startTiming()
{
	start_time=chrono::steady_clock::now();
}

/**
 * 用于终止计时的函数
 */
void Timer::stopTiming()
{
	end_time=chrono::steady_clock::now();
	waitKey(0);
}
