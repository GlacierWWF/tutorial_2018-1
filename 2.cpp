
#include <iostream>

#include <cstdlib>

#include <ctime>

#include <conio.h>

#include <iomanip>

#include <windows.h>

#include <ratio>

#include <chronr> 

using namespace std;

void gotoxy(int x, int y)

{

	COORD pos = {x,y};

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, pos); 

} 

 

void hidden()

{

    	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    	CONSOLE_CURSOR_INFO cci;

	GetConsoleCursorInfo(hOut,&cci);

	cci.bVisible=0;

	SetConsoleCursorInfo(hOut,&cci);

}

 

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

 

Timer::Timer()

{

	is_pause = false;  

	is_stop = true;

}

 

 

bool Timer::isPause()

{	

	if(is_pause)

	return true;

	else

	return false;

}

 

bool Timer::isStop()

{

	if(is_stop)

		return true;

	return false;

} 

 

void Timer::StartTiming()



{	if(is_stop)

	

		start_time = time(0);

		is_stop = false;

	}
	
void Timer::Resume()

{	if(is_pause)



		is_pause = false;

		start_time += time(0)-pause_time; 

	}



 

void Timer::Pause() 

{

	if(is_stop||is_pause)

		return; 

	else   

	{

		is_pause = true;

		pause_time = time(0); 
	}

}

void Timer::StopTiming()   

{

	if(is_stop)
		return ; 

	else if(is_pause)  

	{

		is_pause = false;

		is_stop = true;

	}

	else if(!is_stop)

	{

		is_stop = true;

	} 
}

 

void Timer::show()

{
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    typedef std::chrono::duration<int,std::milli> milliseconds_type;
    cout << "时间为" << time_used.count() << " ms。" << endl;



	gotoxy(35,12);


}

 

int main()

{

	Timer t; 

	char ch; 

	hidden();

	system("color 02"); 

	gotoxy(35,12);

	cout<<"00:00:00";

	gotoxy(20,18);

	cout<<"按a(start)开始，按p(pause)暂停，按s(stop)停止,按r（resume）继续";

	while(1)

	{

		if(kbhit())

		{

			ch = getch();

			switch (ch)

			{

				case 'a':t.StartTiming();break;

				case 's':t.StopTiming();break;

				case 'p':t.Pause();break;

                case 'r':t.Resume();break;
				default :break;

			}

		}

		if(!t.isStop()&&!t.isPause()) 

		{

			t.show();

		}

	}

	

}

 

