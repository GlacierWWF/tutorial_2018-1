/********************************************************************
 * Timer project for SYSU-IARC
 *
 * Week 2 project: Timer
 *
 * This is the definition of the member function of the Timer class
 * and the definition of the global variable.
 *
 *
 * @Author: 杨卓
 * @Revised: 杨卓
 * @Date: 2018-10-6
 * @Version: 1.0.0
 * @Abstract: The definition of the member function of the Timer class
 *  and global variable.
 *
 */

#include<iostream>
#include"op.h"
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace cv;
using namespace std;
using namespace std::chrono;


// 定义全局变量
string str_choice = "";  
double count_time = 0;
double pause_time = 0;
const string str_start = "start";
const string str_stop = "stop";
const string str_quit = "quit";
const string str_pause = "pause";
const string str_resume = "resume";

// 打开欢迎图片
void Timer::open()
{
	img = imread("welcome3.jpeg", CV_LOAD_IMAGE_COLOR);
	if( !img.data )
	{
		cout << "Could nor open or find the image." << endl;

	}
	
	namedWindow("Welcome!" , CV_WINDOW_NORMAL);
	cvResizeWindow("Welcome!" , 700 , 700); //设置窗口大小
	imshow("Welcome!" , img);

	waitKey(0);
	
}


// 进入计时，显示图片
void Timer::startTiming()
{
	string str_time; // 用于在图片上显示时间
	count_time = 0;
	auto start = system_clock::now(); // 记录进入计时的时间点
	
	//当用户输入stop或者quit时，退出循环
	while(str_choice != str_stop && str_choice != str_quit)
	{	
		auto end = system_clock::now();
                auto duration =duration_cast<microseconds>(end - start);
                count_time = double(duration.count()) * microseconds::period::num / microseconds::period::den;

		// 计时时间 = 实际走过时间 - 暂停时间
		count_time = count_time - pause_time;

//		cout << "pause_time is:   " << pause_time << endl;
		
                str_time = to_string(count_time);
		string str_time_show =  str_time.substr(0, str_time.size()-7);
		cout << "Counting:  " << str_time_show << endl;
                str_time = str_time.substr(0, str_time.size()-5);
		
                const string str_text = str_time + "s";

                destroyAllWindows();

                img = imread("Count.jpeg", CV_LOAD_IMAGE_COLOR);
                if( !img.data )
                {
                        cout << "Could nor open or find the image." << endl;
                }
		
		// 设置放在图片上的文本参数
		putText(img , str_text , Point(img.rows/2, img.cols/2), FONT_HERSHEY_COMPLEX , 5 , Scalar(0,0,255), 1 , 8 , false);

                namedWindow("Count" , CV_WINDOW_NORMAL);
                cvResizeWindow("Count" , 700 , 700); //设置窗口大小
                imshow("Count" , img);

		if( str_choice == str_pause)
		{
			cout << "[INFO] Paused." << endl;
			while( !resume() )
			{
				pause();
			}	
		}

		else 
                {
			waitKey(1000);
		}

	}// while	


	if(str_choice == str_stop)	
	{
		stopTiming();
	}
}


// 用于关闭计时窗口，打开欢迎窗口
void Timer::stopTiming()
{
	cout << "[INFO] Stop counting. " << endl;
	cout << "[INFO] Now only 'quit' works. (Believe it or not) " << endl;
	close();
	open();

}

// 关闭所有窗口
void Timer::close()
{
	destroyAllWindows();
}


// 暂停计时功能。实际为计算暂停时间
void Timer::pause()
{
	auto pause_point_time = system_clock::now();

        imshow("Count" , img);
        waitKey(100);

    	auto resume_point_time = system_clock::now();
	auto duration2 =duration_cast<microseconds>(resume_point_time - pause_point_time);
	pause_time = pause_time + double(duration2.count()) * microseconds::period::num / microseconds::period::den;
	     	
	
}

// 恢复计时
bool Timer::resume()
{
	if(str_choice == str_resume)
	{
		cout << "[INFO] Resumed. " << endl;
		return true;
	}
	else 
		return false;
}


