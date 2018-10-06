#include<iostream>
#include<thread>
#include<opencv2/opencv.hpp>
#include"timer.hpp"
using namespace std;

void input()
{
	Timer counter;
	string s;
	thread t4(Timer::open );
	t4.detach();
	while( true )
	{
		cin >> s;
		if( s == "start")
		{
			thread t2(Timer::startTiming);
			t2.detach();
		}else if( s == "stop" )
		{
			thread t3(Timer::stopTiming);
			t3.detach();
		}else if( s == "quit")
		{
			counter.close();
			return;
		}else if( s == "pause" )
		{
			counter.pause();
		}else if( s == "resume" )
		{
			counter.resume();
		}
	}
}

int main()
{
	thread t1(input);
	t1.join();
	return 0;
}
