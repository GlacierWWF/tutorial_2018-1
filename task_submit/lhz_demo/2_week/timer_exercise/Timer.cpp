/*************************************************** 
*Timer.cpp                     
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/5 
*
*Abustract: Implements the header file's functions
			and the main program
***************************************************/ 
#include "Timer.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <chrono>   
#include <unistd.h>
#include <iostream>  
#include <pthread.h>  

using namespace cv;
using namespace std;
using namespace chrono;

/*定义全局变量*/
static double x;
Mat img,img1,img2;

/*这个函数可以新建一个窗口
        并在窗口上显示图片*/
void* Timer::open(void* args)
{
	img = imread("name.jpg",1);
	namedWindow("hello man");
	imshow("hello man", img);
	waitKey(0);
};

/*这个函数使用choro类计时
   并将时间打印到open创建的图片上*/
void* Timer::startTiming(void* args)
{
	auto start = system_clock::now();
	img.copyTo(img1);
	for(;;)
	{
		double a;
		sleep(1);
		auto end   = system_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		a=double(duration.count()) * microseconds::period::num / microseconds::period::den  ;
		char buf[100];
    	sprintf(buf, "%2.1f", a);
    	putText(img1,buf,Point(200,200),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
		imshow("hello man",img1);
		waitKey(100) & 0xFF;
		img.copyTo(img1);

		printf("%2.0f\n",a);
		auto start1=end;
		img2=img1;
		x=a;
		
    }
      	
};

/*这个函数用来停止计时*/
void* Timer::stopTiming(void* args)
{
	void* open();
};

/*这个函数用cv的函数关闭创建的窗口*/
void* Timer::close(void* args)
{
	cvDestroyAllWindows();
};

/*这个函数配合main形成暂停功能*/
void* Timer::pause(void* args)
{
	waitKey(0);
};

/*配合main形成恢复功能*/
void* Timer::resume(void* args)
{
	auto start = system_clock::now();
	for(;;)
	{
		
		double b,c;
		//usleep(100);
		auto end   = system_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		b=double(duration.count()) * microseconds::period::num / microseconds::period::den  ;
		c=b+x;
		printf("%2.0f\n",c);
		char buf1[100];
    	sprintf(buf1, "%2.1f", c);
    	putText(img1,buf1,Point(200,200),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
    	namedWindow("hello man");
		imshow("hello man",img1);
		waitKey(1000);
		img.copyTo(img1);
		
    }
};


int main()
{
	char ch[100];
	double b;
	pthread_t id1,id2,id3,id4;
	cout << "[INFO] Welcome to the counter" << endl;

	/*创建一个线程来open*/
	pthread_create( &id1, NULL, Timer::open, NULL );
	auto start = system_clock::now();

	while(scanf("%s",ch)==1)
	{
			
		/*通过判断输入来创建性的线程实现功能*/
		if (strcmp(ch,"start")==0)
		{
			/*开始计时*/
			cout << "[INFO] Start counting" << endl;
			pthread_create( &id2, NULL, Timer::startTiming, NULL );
		}
		else if (strcmp(ch,"stop")==0)
		{
			/*停止计时*/
			cout<< "[INFO] Stop counting"<<endl;
			pthread_cancel(id2);
			pthread_cancel(id3); 
			pthread_create( &id3, NULL, Timer::stopTiming, NULL );
		}
		else if (strcmp(ch,"quit")==0)
		{
			/*退出程序*/
			cout << "[INFO] Program exited" << endl;
			pthread_create( &id3, NULL, Timer::close, NULL );
			break;
		}
		else if (strcmp(ch,"pause")==0)
		{
			/*暂停计时*/
			cout <<"[INFO] Paused"<<endl;
			pthread_cancel(id2);
			pthread_create( &id3, NULL, Timer::pause, NULL );
		}
		else if (strcmp(ch,"resume")==0)
		{
			/*恢复计时*/
			cout << "[INFO] Resumed" << endl;
			pthread_cancel(id3);
			pthread_create( &id3, NULL, Timer::resume, NULL );
		}
	}
}


