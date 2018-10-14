#include<iostream>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<opencv2/opencv.hpp>
#include"Timer.h"
using namespace cv;
using namespace std;
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
