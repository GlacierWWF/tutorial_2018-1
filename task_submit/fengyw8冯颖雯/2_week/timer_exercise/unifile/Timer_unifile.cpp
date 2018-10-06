#include<iostream>
#include<ctime>//？ 
#include<chrono>
#include<ratio>
#include<iomanip>
#include<unistd.h>
#include<string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

using namespace std::chrono; 

//Timer class definition
class Timer
{	
public:
	int open();
	void startTiming();
	void stopTiming();
	void close();
	void pause();
	void resume();	
};
 

Mat image;

//打开窗口。窗口显示一幅欢迎图片
int Timer::open()
{
	
	image=imread("th.jpg",1) ;//???
	if (image.data == nullptr) //数据不存在,可能是文件不存在
    	{
        	cerr << "文件不存在." << endl;//cerr??? 
        	return 0;
    	}
    else
    {
    	namedWindow("counter");
    	imshow("counter",image);
    	waitKey(0);//多线程 
	return 0;
	}
}

//开始计时。窗口出现秒钟计时显示，终端也同时输出秒数。
//图片窗口计秒数保留至小数点一位，终端计时秒数每秒更新一次
void Timer::startTiming()
{
	//计算时间间隔 
    //std::chrono::steady_clock ，因此要在前面加上 using namespace std::chrono;
    steady_clock::time_point t1 = steady_clock::now();//记录开始时间  
	//for(int i=1;i<10;i++)
	{
		IplImage* pImg = cvLoadImage("th.jpg",1); 
		
		usleep(100000);//单位为ms//暂停0.1s（仅该线程？） 
		imshow("counter",image);
    	steady_clock::time_point t2 = steady_clock::now();//记录第二次时间
    	cout<<2<<endl;
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);//计算时间间隔
		
		CvFont font;  
    	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0f, 1.0f, 0, 5, 8);
    	cvPutText(pImg, "to_string(floor(time_span.count()*10)/10).c_str() s", cvPoint(200, 200), &font, CV_RGB(255,0,0));

		//cvPutText(pImg,to_string(floor(time_span.count()*10)/10).c_str(),cvPoint(50,60),CV_FONT_HERSHEY_SIMPLEX,cv::Scalar(255,23,0));//在图片上写文字
		//pImg, "This is a picture named lena!", cvPoint(50, 50), &font, CV_RGB(255,0,0)
		int i;
		cin>>i;
		
	
	}
	//std::cout << "It took me " << time_span.count() << " seconds."<<endl;//输出时间间隔 
}

void Timer::stopTiming()//结束计时。窗口恢复欢迎图片。
{
	imshow("counter",image);
}

void Timer::close()//关闭窗口。
{
	
} 

void Timer::pause()//暂停计时，窗口保持不变
{
	//wait();
}

void Timer::resume()//从原来秒数继续计时
{
	//notify();
}

int main()
{
	Timer a;
	a.open();
	cout<<"123"<<endl;
	a.startTiming();
	cout<<"123"<<endl;

	
	
	return 0;
}
