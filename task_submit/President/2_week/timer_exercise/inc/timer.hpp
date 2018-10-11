#ifndef __TIMER_HPP
#define __TIMER_HPP

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
#include <atomic>
#include <functional>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Timer
{
public:
	Timer();

	bool open(string path);
	void close();

	void startTiming();
	void stopTiming();

	void pause();
	void resume();

private:
	std::thread _thr;
	std::atomic<bool> _flag;

	void free(Mat&);
	void count(Mat&);

	Mat img;
	clock_t Tstart;
	double T, _T;
	std::function< void(cv::Mat&) > nowFunc, nextFunc;
	void timThread();
};

#endif /* __TIMER_HPP */
