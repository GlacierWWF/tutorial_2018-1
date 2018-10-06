/*****************************************************************
 * @file	Timer.hpp
 * @brief	This file define class Timer.
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


#pragma once
#include<iostream>
#include<string>
#include<opencv2/imgproc/imgproc.hpp> //optional?
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<chrono>

class Timer
{
	public:
		Timer();
		void open();
		void startTiming();
		void stopTiming();
		void close();
		//void pause();
		//void resume();
		void countTime();
	private:
		cv::Mat image;
		std::chrono::steady_clock::time_point start_time;
		std::chrono::steady_clock::time_point end_time;
};
