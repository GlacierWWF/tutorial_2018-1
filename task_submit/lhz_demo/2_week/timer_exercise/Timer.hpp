/***************************************** 
*Timer.hpp                    
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/5 
*
*Abustract: Define header files 
****************************************/ 
#ifndef TIMER_H
#define TIMER_H


class Timer
{
public:
	static void* open(void* args);
	static void* startTiming(void* args);
	static void* startTiming2(void* args);
	static void* stopTiming(void* args);
	static void* close(void* args);
	static void* pause(void* args);
	static void* resume(void* args);


};

#endif