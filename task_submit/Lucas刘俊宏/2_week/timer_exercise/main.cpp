//
//  main.cpp
//  OpenCV_Timer
//
//  Created by liujunhong on 2018/10/4.
//  Copyright © 2018年 liujunhong. All rights reserved.
//
#include "head.h"
#define WINDOW_NAME "window"
Mat image = imread("/Users/liujunhong/Documents/空队考核/Week2/Timer/OpenCV_Timer/OpenCV_Timer/sky.jpg");
cv::Mat frame = image;
Mat image2;

int Timer::open()
{
    cv::namedWindow(WINDOW_NAME);
    cvui::init(WINDOW_NAME);
    cvui::button(frame, 100, 80, "start");
    cvui::button(frame, 110, 80, "stop");
    cvui::button(frame, 120, 80, "close");
    resize(image,image2,Size(850,600),0,0,CV_INTER_LINEAR);
    imshow(WINDOW_NAME, image2);
    return 0;
}

int64 Timer::getTimeTicks()
{
    return sumTime;
}
double Timer::getTimeMicro()
{
    return (double)getTimeTicks()/cvGetTickFrequency();
}
double Timer::getTimeSec()
{
    return getTimeMicro()*1e-6;
}
int64 Timer::getCounter()
{
    return counter;
}
void Timer::startTiming()
{
    string time;
    while(1)
    {
        startTime = cvGetTickCount();
        sleep(100);
        int64 endTime = cvGetTickCount();
        time = (endTime - startTime)/cvGetTickFrequency() * 1e-6;
        putText(image2,time,Point(110,60),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);//在图片上写文字
        namedWindow(WINDOW_NAME);
        imshow(WINDOW_NAME, image2);
    }
}
void Timer::stopTiming()
{
    return;
}
void Timer::close()
{
    cvDestroyWindow(WINDOW_NAME);
}
std::ostream& operator<<(std::ostream& out, Timer& tm)
{
    return out << tm.getTimeSec() << "s";
}
int main(int argc, char* argv[])
{
    Timer tm;
    tm.open();
    if(cvui::button(frame, 100, 80, "start"))
    {
        tm.startTiming();
    }
    if(cvui::button(frame, 110, 80, "stop"))
    {
        tm.stopTiming();
    }
    if(cvui::button(frame, 120, 80, "close"))
    {
        tm.close();
    }
    tm.startTiming();
    waitKey();
    return 0;
}
