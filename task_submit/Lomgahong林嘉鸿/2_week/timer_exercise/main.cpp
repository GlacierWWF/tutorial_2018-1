/*****************************************************************
 * @file	main.cpp
 * @brief	This programme can run the timing project.
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


#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<chrono>
#include<thread>
#include"Timer.hpp"

using namespace std;

/**
 * 这个函数用于处理第二线程
 * 参数：代表用户选择的choise，类型为string
 *       T，类型为Timer
 */
void show(Timer T,string choise)
{
	while(true)	
	{
		//判断用户输入
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

