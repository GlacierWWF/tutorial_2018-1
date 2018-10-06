/*Title:IP.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-10-04
*Version:1.0.0
*Abstract: A main.cpp file to finish a timer.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<opencv2/opencv.hpp>
#include"Timer.h"
using namespace cv;
using namespace std;
Timer::Timer()
{
	time = "00.0";
	is_pause = false; 
	is_stop = true;
}
bool isPause(Timer &a)
{
	if (a.is_pause)
		return 1;
	return 0;
}
bool isStop(Timer &a)
{
	if (a.is_stop)
		return 1;
	return 0;
}
void open()
{
	Mat image = imread("E:\\test.jpg");
	namedWindow("Welcome");
	cv::putText(image, "Please enter the instruct", Point(20,170), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 4, 8);
	cv::imshow("Welcome", image);
	waitKey(10);
}
void display(string a)
{
	Mat image = imread("E:\\test.jpg");
	namedWindow("Welcome");
	cv::putText(image, a, Point(180, 180), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4, 8);
	cv::imshow("Welcome", image);
	waitKey(10);
}
Timer startTiming(Timer a)
{
	cout << "start counting" << endl;
	if (a.is_stop)
	{
		a.is_stop = 0;
	}
	else if (a.is_pause)
	{
		a.is_pause = 0;
	}
	display(a.time);
	while (1)
	{
			    sleep(0.1);
				a.time[3] += 1;
				if (a.time[3] > '9')
				{
					a.time[3] = '0';
					a.time[1] += 1;
					cout << a.time[1] << endl;
					{
						if (a.time[1] > '9')
						{
							a.time[1] = '0';
							a.time[0] += 1;
						}
					}
				}
				display(a.time);
		
		
	}
	return a;
}
void stopTiming(Timer &a)
{
	cout << "stop counting" << endl;
	a.time = "00.0";
	display(a.time);
}
void pause(Timer &a)
{
	cout << "pause" << endl;
}
void resume(Timer &a)
{
	cout << "resume" << endl;
}
void close()
{
	exit(0);
}
int main()
{
	Timer x;
	x.time = "00.0";
	cout << "Welcome to the counter."<<endl;
	//for (int i = 0; i <= n; i++)
	open();
	while(1)
	{   
		string input;
		std::cin >> input;
			if (input == "start")
			{
				startTiming(x);
			}
			if (input == "stop")
			{
				stopTiming(x);
			}
			if (input == "pause")
			{
				pause(x);
			}
			if (input == "resume")
			{
				resume(x);
			}
			else if (input == "quit")
				close();
	}
	return 0;
}
