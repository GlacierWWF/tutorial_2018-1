/*********************************************************
 * Timer
 *
 * @author	Floyed_Shen
 * @email	Floyed_Shen@outlook.com
 * @version	1.0.0.0
 * @date	2018/10/4
 */
#ifndef TIMER_H
#define TIMER_H
#include "timer.h"
#include <opencv2/opencv.hpp>
#include <thread>
using namespace cv;
using namespace std;
class Timer{
    private:
        int dur,tmp;
        int second_now;
        Mat mat;
        Point org;
        char tim_str[50];
        const char window_name[6]="timer";
        const char author_name[12]="Floyed_Shen";
        thread input;
        int action;
        friend void scan();//读入用户终端命令
        void startTiming();//开始计时
        void stopTiming();//停止计时
        void pause();//暂停
        void resume();//从暂停恢复计时
        void write(const int& );//写入图片，更新时间
        void run();//进入计时循环
        void int2str(int);//整数转化为字符数组
    public:
        Timer();
        ~Timer();
        void open();//在程序中调用此函数、开始运行计时器


};
#endif