/***********************************************************************
 *
 *  the header file of timer
 *
 *  @file 	timer.h
 *  @brief	Timer类及相关函数的声明
 * 
 *
 *  该timer类的成员函数有：open()    startTiming()   stopTiming()
 *  			   close()   pause()         resume() 
 *  实现了一个计时器对象的基本功能
 *
 *
 *  @author	马飞鹏
 *  @email      767102280@qq.com
 *  @version 	1.0.1
 *  @date	2018/10/3
 *
 *
 *  ------------------------------------------------
 *  修改历史：
 *  <日期>    |  <版本> |  <作者>  |  <描述>
 *  ------------------------------------------------
 *  2018/10/2 |  1.0.0  |  马飞鹏  | 创建文件 
 *  ------------------------------------------------
 *  2018/10/3 |  1.0.1  |  马飞鹏  | 添加完整注释
 *  ------------------------------------------------
 ***********************************************************************
 */

#ifndef __TIMER_H
#define __TIMER_H

#include<iostream>
#include<chrono>
#include<string>
#include<sstream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

/**
 * @brief 包含了chrono库的一些比较长的命名空间
 *
 * 将用的比较多的 time_point,duration,duration_cast
 * steady_clock所在的命名空间先定好，使代码看起来不
 * 会太冗长。
 */
namespace my_timer
{
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::steady_clock;
}
using namespace my_timer;



/**
 * @brief  Timer类实现一个计时器的基本功能
 * 
 * 实现的功能有：打开可视化界面，开始计时，
 * 暂停计时，恢复计时，停止计时，关闭界面
 *
 */
class Timer
{
	steady_clock::time_point  start_time;   	///<计时器计时的开始时间
	steady_clock::time_point  end_time;		///<计时器计时结束的时间
	cv::Mat welcome_image;				///<欢迎界面的图片
	double dur_time;				///<如果计时器暂停了，该变量用来记录暂停前经过的秒数
	double before;					///<为了在终端每隔一秒输出一次时间，该变量记录相隔时间的前一个时刻
	double after;					///<该变量记录后一个时刻
	bool is_timing;					///<是否正在计时
	bool is_stoping;				///<是否停止计时
	bool is_closed;					///<是否关闭窗口
	bool is_pausing;				///<是否暂停计时
	bool is_open;
  public:
	  Timer();		//构造函数
	  void open();		//打开可视化界面窗口
	  void startTiming();	//开始计时
	  void stopTiming();	//停止计时，窗口恢复欢迎界面
	  void close();		//关闭窗口
	  void pause();		//暂停计时
	  void resume();	//恢复计时
	  void show();		//显示计时的秒数，精确到小数点后一位
};


#endif    /* __TIMER_H */
