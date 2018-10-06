//
//  timer_client.hpp
//  timer
//
//  Created by 张涵健 on 2018/10/5.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#ifndef timer_client_hpp
#define timer_client_hpp
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <string>
#include <stdlib.h>
#include<iomanip>
using namespace cv;
using namespace std;

#define picture "IMG_3222.png"

class Timer{
private:
    double start;
    bool _execute;
    bool _run;
    double pause_time;
    bool _pause;
    bool _stop;
public:
    Timer();
    void open();
    void startTiming();
    void stopTiming();
    void close();
    void pause();
    void resume();
    void time();
    void picture_show(string str);

};
#endif /* timer_client_hpp */
