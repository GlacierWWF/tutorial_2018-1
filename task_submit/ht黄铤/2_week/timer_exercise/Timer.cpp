#include "Timer.h"
//#include <boost/timer.hpp> 
#include <iostream> 
#include<opencv2/opencv.hpp>
//using namespace boost;
using namespace std;
//using namespace chrono;
//using namespace boost::chrono;

bool Timer::ispause()
{
	if(is_pause)
		return true;
	else return false;
}

bool Timer::isstop()
{
	if(is_stop)
		return true;
	else return false;
}

void Timer::open()
   {
	   Mat image=imread("https://www.baidu.com/link?url=D5242WTF5rp-BHSptRJL8xyglv2nI3CWcT8mF-ngY49JtvOLRC1_ynelCYzTkhQivOczfxnFLlwjTk1aeLnxt0nMUxomYtgj85R_Ib8ZzFZKMeOibnxCfgE655XkCSucowpv66mtJsyI-H056YhOcqubI6NgeVoXyUk6jhb6kxBCXN_rH2V2KYhGIm1HJRiJVKGLjYQqS41eh-TxbVLwbxguODcEaIMrqhDhUEoKda2GIXXM8ukRpcy36t1GvI-MBDST24TQgZxjBbLDkMknQ4Jk2GPunLikuwlrfliCGduwPW8V6Cqw4MhOcXvd2NGskf0iUmu-DtRPLt55emDBLUd_hVNmvf5hhQJ-1wwCZZ_S7toZpR_6tkReh2U5MjCuS7bfwCqzcrPTYMTz0E89237eooBjQblg0A1hLrNU9UQHI9mjkZx9OcU3VEJ5b_M3095s3RDcisqusEYG3p35qVmFRgIN3GnVPLQM5mlp3IOjB8fqMdAKnx8SkNVhHQDAMJVIqUYX_PV0t_m7shTKxkHSd7xr8zzdWHTZ5usYHeZVKXUcUYMttNMd_R08-A2SzwBenXb-iSt9YyzLyGuy_Ja4KutI4z7EZzb5JY6LuAS-hh91lC7R3RL0ReSWOOX6bHuAZPWv5Di6DUhsZEcW8VZ5tVGVoay9mTVxmiglfDC&timg=https%3A%2F%2Fss0.bdstatic.com%2F94oJfD_bAAcT8t7mm9GUKT-xh_%2Ftimg%3Fimage%26quality%3D100%26size%3Db4000_4000%26sec%3D1538715514%26di%3Dbe9a653cf8ee47c9f9bc5cd59a16e20b%26src%3Dhttp%3A%2F%2Fimgsrc.baidu.com%2Fforum%2Fw%3D580%2Fsign%3D4976c1668f01a18bf0eb1247ae2e0761%2Fe1eb02728bd4b31c45a3d3f18fd6277f9f2ff8e1.jpg&click_t=1538715520533&s_info=791_573&wd=&eqid=e4871fbe00020edb000000065bb6ef79");
	   namedWindow("window");
	   imshow("window",image);
	   waitKey(0);
   }



void Timer::startTiming()
{
	if(is_stop)
	{		
		start_time = time(0);	
		is_stop = false;	
	}	
	else if(is_pause)	
	{	
		is_pause = false;	
		start_time += time(0)-pause_time;	
	}

}


void Timer::stopTiming()
{
	if(is_stop) 
		return ; 
	else if(is_pause)
	{		
		is_pause = false;	
		is_stop = true;	
	}	
	else if(!is_stop)	
	{		
		is_stop = true;
	} 

}

void Timer::close()
{
	return 0;
}

void Timer::pause()
{
	if(is_stop||is_pause) 
		return; 
	else
	{
		is_pause = true;
		pause_time = time(0);
	}

}
void Timer::show()
{
	long t = time(0) - start_time;	
	gotoxy(35,12);
	cout<<setw(2)<<setfill('0')<<t/60/60<<":"
		<<setw(2)<<setfill('0')<<t/60<<":"
		<<setw(2)<<setfill('0')<<t%60<<endl;
}

void Timer::resume()
{
	is_pause=false;
}





