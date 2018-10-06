#ifndef TIMER_HPP
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace std::chrono;
using namespace cv;

class Timer
{
  public:
    time_point<std::chrono::steady_clock> startPoint;
    time_point<std::chrono::steady_clock> pausePoint;
    time_point<std::chrono::steady_clock> resumePoint;
    Mat backGround;

    Timer();
    void Open();
    void startTiming();
    void stopTiming();
    void close();
    void pause();
    void resume();
    float getDuration();
    void show();

    ~Timer();

    bool isCounting;
};

#endif // !TIMER_HPP


