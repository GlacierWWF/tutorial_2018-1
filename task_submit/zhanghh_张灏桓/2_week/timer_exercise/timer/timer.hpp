//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_6
//Version:v1.0.0
//Abstract:header file of timer



#ifndef TIMER
#define TIMER

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <ratio>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#pragma comment(lib,"opencv_world330.lib")

using namespace cv;
using namespace std;
using namespace std::chrono;

int states = -1; //
Mat image, ori_image;//store the background image
class Timer
{
 public:
  
  Timer();
  void working();
  static void show();
  static void control();
  static void open();
  static void startTiming();
  static void stopTiming();
  static void close();
  static void pause();
  static void resume();
};

#endif
