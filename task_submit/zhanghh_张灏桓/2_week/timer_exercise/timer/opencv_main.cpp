//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_6
//Version:v1.0.0
//Abstract:A timer with startTiming, stopTimming pause and resume.

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <ratio>
#include <pthread.h>
#include<opencv2/opencv.hpp>
#include "timer.cpp"
#pragma comment(lib,"opencv_world330.lib")

using namespace cv;
using namespace std;
using namespace std::chrono;

int main( int argc, char** argv )
{
  image = imread("1.png", 1);//read the background image
  ori_image = image.clone();
  if(!image.data)//check the existence of image
  {
    printf( " No image data \n " );
    return -1;
  }
  Timer my_timer = Timer();
  my_timer.working();

  return 0;
}

 
