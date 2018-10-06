/***********************************************************
 * Timer project for SYSU-IARC
 *
 * Week 2 project: Timer
 *
 * This is the declaration of the member function of the class Timer
 * and the global variable
 *
 * @Author: 杨卓
 * @Revised: 杨卓
 * @Date: 2018-10-6
 * @Version: 1.0.0
 * @Abstract: The declaration of the member function of the class Timer
 * and the global variable.
 */


#ifndef _OP_H
#define _OP_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

extern string str_choice; // 存储用户输入
extern double count_time ;  // 计时时间
extern const string str_start ; 
extern const string str_stop ;
extern const string str_quit ;
extern const string str_pause ;
extern const string str_resume ;
extern double pause_time;


class Timer
{
        private:

		Mat img;

        public:
                void open();
              	void startTiming();
                void stopTiming();
                void close();
             	void pause();
        	bool resume();
                
};

#endif

