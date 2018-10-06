//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_6
//Version:v1.0.0
//Abstract:A timer with startTiming, stopTimming pause and resume.

#include "timer.hpp"

Timer::Timer(){}

void Timer::working() //working function, creating 2 thread
{
  
  thread th1(show);
  thread th2(control);
  th1.join();
  th2.join();
}

void Timer::control() //get input and control the timer
{
  string command = "";
  while(command != "quit")
  {
    cin >> command;
    if(command == "begin")
    {
      open();
      startTiming();
    }
    else if(command == "stop")
    {
      stopTiming();
    }
    else if(command == "pause")
    {
      pause();
    }
    else if(command == "resume")
    {
      resume();
    }
    else if(command == "quit")
    {
      close();
    } 
  }
}

void Timer::open() //open the image window
{
  states = 0;
}

void Timer::startTiming() //start to time
{
  states = 1;
}

void Timer::stopTiming() //stop timing
{
  states = 2;
}

void Timer::pause() //pause timming
{
  states = 3;
}

void Timer::resume() //resume timming
{
  states = 4;
}

void Timer::close() //close the timing window
{
  states = 5;
}

void Timer::show()
{
  auto start = steady_clock::now();
  auto end = steady_clock::now();
  auto tt = duration_cast<microseconds>(end - start);
  int saved_time = 0; //store the time for resume
  while(states)
  {
    if(states == 0)
    {
      namedWindow( "timer", CV_WINDOW_AUTOSIZE );
      imshow( "timer", image );//show the image, without timing
    }
    else if(states == 1)
    {
      start = steady_clock::now();//record the begin time
      while(states == 1)
      {
        end = steady_clock::now();//current time
	tt = duration_cast<microseconds>(end - start);//length of time
	image = ori_image.clone();
        cv::Point p = cv::Point(50,image.rows/4);//position of time in the image
	char show_time[10];
	sprintf(show_time, "%.1f", (float(tt.count()/100000 + saved_time))/10);
	string time_str = show_time;
        cv::putText(image, time_str, p, cv::FONT_HERSHEY_TRIPLEX, 1.8, cv::Scalar(255, 200, 200), 2, CV_AA);
        

        namedWindow( "timer", CV_WINDOW_AUTOSIZE );
        imshow( "timer", image );//show the image
	waitKey(10);
      }
      saved_time = tt.count()/100000 + saved_time;
    }
    else if(states == 2)
    {
      saved_time = 0;
      image = ori_image.clone();
      namedWindow( "timer", CV_WINDOW_AUTOSIZE );
      imshow( "timer", image );//显示图片
      waitKey(10);
    }
    else if(states == 3);
    else if(states == 4)
    {
      states = 1;
    }
    else if(states == 5)
    {
      destroyWindow("timer");
      break;
    }
  }
}


