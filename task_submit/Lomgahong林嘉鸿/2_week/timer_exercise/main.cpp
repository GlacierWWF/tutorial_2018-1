#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<chrono>
#include<thread>
#include"Timer.hpp"

using namespace std;

void show(Timer T,string choise)
{
	while(true)	
	{
		getline(cin,choise);
		if(choise=="start")
		{
			T.startTiming();
		}
		else if(choise=="stop")
		{
			T.stopTiming();
		}
		else
		{
			break;
		}
	}
}

int main(int argc,char** argv)
{
	Timer T;
	T.open();
	string choise;
	thread count(show,ref(T),ref(choise));
	count.detach();
	while(choise!="exit")
	{	
		T.countTime();
	}
	T.close();
	return 0;
}

