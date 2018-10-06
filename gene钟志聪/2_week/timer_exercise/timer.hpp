#include<iostream>
#include<thread>
#include<string>
#include<ctime>
#include<opencv2/opencv.hpp>
//#define DEBUG
using namespace cv;
using namespace std;

class Timer
{
public:
	//open the window and show an image
	static void textImage(string text); //往图片输出文字	
	static void open(); //开始运行
	static void startTiming();//开始计时
	static void stopTiming();//停止计时
	void close();//关闭
	void pause();//暂停
	void resume();//继续
private:
	static bool stopFlag;
	static bool startFlag;
	static bool closeFlag;
	static bool endFlag;
	static bool pauseFlag;
	static clock_t beg;
	static clock_t current;
	static Mat image;
	static string path;
};

