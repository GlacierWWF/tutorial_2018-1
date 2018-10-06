//
//  head.h
//  OpenCV_Timer
//
//  Created by liujunhong on 2018/10/4.
//  Copyright © 2018年 liujunhong. All rights reserved.
//

#ifndef head_h
#define head_h
#include <iostream>
#include <string.h>
#include "cvui.h"
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Timer
{
public:
    int open(); //打开窗口。窗口显示一幅欢迎图片
    void startTiming(); //开始计时。窗口出现秒钟计时显示，终端也同时输出秒数
    int64 getTimeTicks(); //返回运行时间的tickcount
    double getTimeMicro(); 
    double getTimeSec(); //以秒为输出单位
    int64 getCounter(); //返回的是调用stop的次数
    void stopTiming();
    void close();
    void pause();
    void resume();
private:
    int64 counter;
    int64 sumTime;
    int64 startTime;
    
    
};
//同时重载ostream，可以方便的以s为单位直接输出
CV_EXPORTS std::ostream& operator<<(std::ostream& out, Timer& tm);
#endif /* head_h */
