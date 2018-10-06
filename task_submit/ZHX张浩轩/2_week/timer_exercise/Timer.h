#ifndef _TIMER_H_
#define _TIMER_H_
#include"opencv2/opencv.hpp"
using namespace cv;
class Timer
{
private:
    Mat time_img;
    int int_count;//终端输出
    float point_count;//图片上的输出
    bool if_continue;//作为判断暂停的一个记号
public:
    Timer();
    void open();
    void startTiming(float pass_time = 0);
    void stopTiming();
    void close();
    void pause();
    void resume();
    float get_float();
};
#endif