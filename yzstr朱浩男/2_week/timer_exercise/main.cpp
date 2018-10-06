
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include "Timer.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace std::chrono;
using namespace cv;

void timing(Timer &timer, int x);

int main()
{

    Timer timer;
    t1.open();
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "start")
        {
            thread t0(timing, timer, 1);
        }
        if (cmd == "stop")
        {
            thread t0(timing, timer, 0);
        }
        if (cmd == "pause")
        {
            thread t0(timing, timer, 2)
        }
        if (cmd == "resume")
        {
            thread t0(timing, timer, 3)
        }
    }

    waitKey(0);
    return 0;
}

void timing(Timer &timer, int x)
{
    if (x == 0)
    {
        timer.stopTiming();
    }
    if (x == 1)
    {
        timer.startTiming();
    }
    if (x == 2)
    {
        timer.pause();
    }
    if (x == 3)
    {
        timer.resume();
    }
}