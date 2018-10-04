/***********************************************************************
 *
 *  the source file of timer
 *
 *  @file 	timer.cpp
 *  @brief	Timer类及相关函数的定义
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
 *
 ***********************************************************************
 */

#include "../inc/timer.h"

/**
 * @brief 	构造一个Timer对象,初始化成员变量
 * @param	无
 * @retval	无
 */
Timer::Timer()
{
  	 is_timing = false;     
	 is_stoping = false;
         is_pausing = false;
	 is_closed = false;
	 is_open = false;
	 dur_time = 0;
	 welcome_image = cv::imread("./bin/welcome.jpg",cv::IMREAD_COLOR);
  	 cv::namedWindow("Timer");
	 
}

/**
 * @brief 	打开计时器的欢迎窗口界面
 * @param 	无输入参数
 * @retval 	无返回参数
 */
void Timer::open()
{
	is_open = true;
}

/**
 * @brief 	计时器开始计时
 * @param 	无输入参数
 * @retval 	无返回参数
 */
void Timer::startTiming()
{
	is_open = false;
	is_timing = true;
	is_stoping = false;
	start_time = steady_clock::now();
	before = 0;
}

/**
 * @brief 	停止计时并返回欢迎窗口
 * @param 	无输入参数
 * @retval 	无返回参数
 * */
void Timer::stopTiming()
{
	is_open=false;
	is_stoping = true;
	is_timing = false;
	is_pausing = false;
}


/**
 * @brief 	关闭计时器窗口
 * @param 	无输入参数
 * @retval 	无返回参数
 * */
void Timer::close()
{
	cv::destroyWindow("Timer");
	exit(0);
}

/**
 * @brief 	暂停计时，显示的秒数不动
 * @param 	无输入参数
 * @retval 	无返回参数
 * */
void Timer::pause()
{
	std::chrono::duration<double> time_span;
	is_pausing = true;
	is_open = false;
	is_timing = false;
	end_time = steady_clock::now();
	time_span = duration_cast<duration<double>>(end_time - start_time);
	dur_time += time_span.count();
}


/**
 * @brief 	恢复计时，从暂停之间的时间继续计时
 * @param 	无输入参数
 * @retval 	无返回参数
 * */
void Timer::resume()
{
	is_pausing = false;
	is_timing = true;
	is_open = false;
	start_time = steady_clock::now();
}


/**
 * @brief 	显示秒数变化，并对计时器的状态作出反应
 * @param 	无输入参数
 * @retval 	无返回参数
 * */
void Timer::show()
{
	if(is_timing==true)
	{	
		double seconds;
		std::string text;
		cv::Mat temp;
		temp = welcome_image.clone();
		duration<double>time_span = duration_cast<duration<double>>(steady_clock::now()-start_time);
		seconds = time_span.count() + dur_time;
		after = seconds;
		text = std::to_string(seconds);
		text = text.substr(0,text.size()-5);
		cv::putText(temp,text+" s",cv::Point(75,150),cv::FONT_HERSHEY_SIMPLEX,3,cv::Scalar(255,0,0),5,8,false);	
		cv::imshow("Timer",temp);
		if((after - before)>=1)
		{
			std::cout<<(int)seconds<<std::endl;
			before = after;
		}
			
		cv::waitKey(10);
	}
	if(is_stoping==true&&is_pausing==false)
	{
		cv::imshow("Timer",welcome_image);
		cv::waitKey(100);
	}
	if(is_stoping==true&&is_pausing==true)
	{
		cv::Mat temp = welcome_image.clone();
		std::string text;
		std::stringstream ss;
		ss<<dur_time;
		text = std::to_string(dur_time);
		text = text.substr(0,text.size()-5);
		cv::putText(temp,text+" s",cv::Point(75,150),cv::FONT_HERSHEY_SIMPLEX,3,cv::Scalar(255,0,0),5,8,false);
		cv::imshow("Timer",temp);
		cv::waitKey(10);
	}
	if(is_open==true)
	{
		cv::imshow("Timer",welcome_image);
		cv::waitKey(100);
	
	}
	if(is_closed==true)
	{
		this->close();
	}

}


