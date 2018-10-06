/*******************************************************
 * Timer project for SYSU-IARC
 *
 * Week 2 project: Timer
 *
 * This is Main function for the 'Timer' project.
 *
 * @Author:  杨卓
 * @Revised: 杨卓
 * @Date: 2018-10-6
 * @Version: 1.0.0
 * @Abstract: In Main function, user can use the timer by commands.
 *    For example:
 * 	start	: start timing
 * 	stop	: stop timing
 * 	pause	: pause timing
 * 	resume	: continue to time
 * 	quit	: exit the program
 */



// System Headers
#include"op.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace cv;
using namespace std;

/**
 * @brief 传递给线程的函数，用于计时,显示图片。
 *
 */
void* thread_timing(void *t1);


/**
 * @brief Timer project Main Function
 *
 * @return integer
 */
int main()
{
	pthread_t p_count; // 创建线程ID  
	Timer t1; // 创建Timer类成员 

	cout << "[INFO] Welcome to my bug! " << endl;
	
	//调用Timer类的open()函数，打开欢迎图片
	t1.open();

	//确认用户输入start, 启动计时
	while(1)
	{
		cout << "[INFO] Input  'start'  to  continue " << endl;
		cin >> str_choice;

		if(str_choice == str_start)	
		{
			cout << "[INFO] Start counting. " << endl;
			break;
		}
		else 
			cout << "[INFO] Input  'start'  to  continue" << endl;
	}

	//创建计时线程
	int ret = pthread_create(&p_count , NULL , thread_timing , (void*)&t1 );
	if(ret != 0)
	{
		cout << "pthread_create error: error_code =  " << ret << endl;
	}

	
	//main里一直读取输入
	while(1)
	{
		cin >> str_choice;
		
		cout << "[INFO] Now your command is :  " << str_choice << endl;
		
		//当用户输入为quit，则调用Timer类close()函数，关闭窗口并退出输入循环
		if(str_choice == str_quit) 
		{
			t1.close();
			break;
		}	

	}

	cout << "[INFO] Congratulation! You finally exit the bug!" << endl;	
	return 0;

}// main


/**
 * @brief 传递给线程的函数，用于计时，显示图片
 */
void* thread_timing(void *t1)
{		
	Timer* tp;  // 创建指向Timer类的指针，用于指向传入的参数t1
	tp = (Timer*)t1; 

	//调用Timer类的startTiming()函数
	tp->startTiming(); 
	
	return 0;	
}


