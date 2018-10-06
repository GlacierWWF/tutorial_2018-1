#ifndef JISHIQI_H
#define JISHIQI_H
#include "iostream"

#include "cstdlib"

#include "ctime"

#include "conio.h"

#include "iomanip"

#include "windows.h"

class Timer

{

	private:

		long start_time;

		long pause_time;


		bool is_pause; 

		bool is_stop;

	public:

		Timer();

		bool isPause(); 

		bool isStop();

	
		void StartTiming(); 

		void Pause();

		void StopTiming();
	
		void Resume(); 

		inline long getStartTime() {return start_time;}

		void show();

};
#endif

