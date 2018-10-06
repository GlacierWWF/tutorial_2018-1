/*Title:IP.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-10-04
*Version:1.0.0
*Abstract: A head file to describe IP class
*/
#pragma once
#define TIMER_H
#include<iostream> 
#include<string>
#include<cstdio>
#include<opencv2/opencv.hpp>
using namespace std;
class  Timer
{
public:
	string time;
	bool is_pause;
	bool is_stop;

	//string seconds;
	Timer();
	bool isPause(Timer &a);
	bool isStop(Timer &a);
	void open(Timer &a);
	Timer startTiming(Timer a);
	void stopTiming(Timer &a);
	void pause(Timer &a);
	void resume(Timer &a);
	void close();
};
