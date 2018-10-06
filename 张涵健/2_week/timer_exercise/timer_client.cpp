//
//  timer_client.cpp
//  timer
//
//  Created by 张涵健 on 2018/10/5.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "timer_client.h"
Timer::Timer(){
    _execute = false;
    _run = true;
    _pause = false;
    _stop = false;
}

void Timer::open(){
    cout << "[INFO] Welcome to the counter." << endl;
    _run = true;
    string command;
    while(_run){
        cin >> command;
        if (command.compare("start")==0) startTiming();
        else if (command.compare("pause")==0) pause();
        else if (command.compare("resume")==0) resume();
        else if (command.compare("quit")==0) close();
        else if (command.compare("stop")==0) stopTiming();
    }
}

void Timer::startTiming(){
    cout << "[INFO] Start counting." << endl;
    start = static_cast<double>(getTickCount());
    _execute = true;
    _stop = false;
    _pause = false;
}

void Timer::stopTiming(){
    cout << "[INFO] Stop counting." << endl;
    _execute = false;
    _stop = true;
}

void Timer::close(){
    cout << "[INFO] Program exited." << endl;
    _run = false;
}

void Timer::pause(){
    cout << "[INFO] Pause." << endl;
    pause_time = static_cast<double>(getTickCount());
    _execute = false;
    _pause = true;
}

void Timer::resume(){
    if(_pause && !_stop){
        cout << "[INFO] Resume." << endl;
        start = start + static_cast<double>(getTickCount()) - pause_time;
        _execute = true;
        _pause = false;
    }
}

void Timer::picture_show(string str){
    Mat src = imread("IMG_3222.png");
    Point end = cv::Point(src.cols/3, src.rows*3/5);
    putText(src, str, end, cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(255, 255, 255), 2);
    imshow("src",src);
    waitKey(10);
}

void Timer::time(){
    picture_show("Welcome!");
    thread control (&Timer::open,this);
    control.detach();
    double fore_time = 0;
    double this_time;
    while(_run){
        //cout << "?" << endl;
        while(_execute){
            this_time = (((double)getTickCount()-start)/getTickFrequency());
            if ((int)this_time > (int)fore_time)
                cout << (int)this_time << endl;
            if ((int)(this_time*10) > (int)(fore_time*10)){
                stringstream ss;
                ss << setiosflags(ios::fixed) << setprecision(1) << this_time << flush;
                string str = ss.str();
                picture_show(str);
            }
            fore_time = this_time;
        }
        if (_stop)
            picture_show("Welcome!");
    }

}
