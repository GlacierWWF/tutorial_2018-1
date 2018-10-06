#include<string>
#include<string.h>
#include<iostream>
//#include<windows.h>
#include<iomanip>
#include <time.h>


using namespace std;
//using namespace cv;
class Timer
{
public:
   Timer()
   {
	   is_pause=false;
	   is_stop=true;
   }
   long getStartTime() {return start_time;} 
   bool ispause();
   bool isstop();
  // void open();
   void startTiming();
   void stopTiming();
   void close();
   void pause();
   void resume();
   void show();
private:
   bool is_pause;
   bool is_stop;
   long start_time; 
    long pause_time;
};


