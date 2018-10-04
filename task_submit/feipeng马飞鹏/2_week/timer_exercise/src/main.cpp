/***********************************************************************
*
*  the main file of timer
*
*  @file       main.cpp
*  @brief      主要处理输入与输出
*
*
*  @author     马飞鹏
*  @email      767102280@qq.com
*  @version    1.0.1
*  @date       2018/10/3
*
*
*  ------------------------------------------------------------
*  修改历史：
*  ------------------------------------------------------------
*  <日期>    |  <版本> |  <作者>  |  <描述>
*  ------------------------------------------------------------
*  2018/10/2 |  1.0.0  |  马飞鹏  | 创建文件
*  ------------------------------------------------------------
*  2018/10/3 |  1.0.1  |  马飞鹏  | 添加完整注释
*  ------------------------------------------------------------
*  2018/10/3 |  1.0.2  |  马飞鹏  | 修复了必须在窗口处有
*            |         |          | 按键输入才能开始计时的bug
*  ------------------------------------------------------------
*/

#include<iostream>
#include "../inc/timer.h"
#include<opencv2/opencv.hpp>
#include<thread>

Timer timer;
/*
 * @brief  该函数在子线程中调用，实现了计时器的窗口界面输出
 * @param  无
 * @retval 无
 *
 */
void output()
{
	while(1)
	{
	timer.show();
	}
}

/*
 * @brief  主函数，创建子线程，同时处理输入和输出
 * @param  无
 * @retval 无
 */
int main()
{
	std::string status;
	timer.open();
	std::thread t(output); 
	while(std::cin>>status)
	{
	if(status =="start")
		timer.startTiming();
	if(status =="quit")
		timer.close();
	if(status =="pause")
		timer.pause();
	if(status =="resume")
		timer.resume();
	if(status =="stop")
		timer.stopTiming();
	}

}
