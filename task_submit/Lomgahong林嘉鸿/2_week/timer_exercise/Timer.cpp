#include"Timer.hpp"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<chrono>

using namespace std;
using namespace cv;

Timer::Timer()
{
	image=cv::imread("Image");
}

void Timer::countTime()
{
 	std::chrono::steady_clock::time_point justnow;
	justnow=chrono::steady_clock::now();
	std::chrono::milliseconds time_b;
	time_b=chrono::duration_cast<chrono::milliseconds>(justnow-end_time);
	stringstream output_stream;
	output_stream<<"Time:"<<time_b.count()<<"ms";
	string output_string;
	output_string=output_stream.str();
	cv::Point xy;
	xy.x=0;
	xy.y=512;
	cv::putText(image,output_string,xy,FONT_HERSHEY_DUPLEX,4,Scalar(255),4,false);
	cv::imshow("Timer",image);
	image=cv::imread("Image.png");
	cv::waitKey(1);
}
		
void Timer::open()
{
	image=cv::imread("Image.png");
	cv::namedWindow("Timer",512);
	cv::imshow("Timer",image);
	cv::waitKey(1);
}

void Timer::close()
{
	cv::destroyWindow("Timer");
}

void Timer::startTiming()
{
	start_time=chrono::steady_clock::now();
}

void Timer::stopTiming()
{
	end_time=chrono::steady_clock::now();
	waitKey(0);
}
