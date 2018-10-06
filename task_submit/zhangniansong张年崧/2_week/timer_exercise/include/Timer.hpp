/* Title: Timer.hpp
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-10-06
 * Version: 1.0.0
 * Abstract: Header file of Timer class
 */

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* time point definition */
typedef std::chrono::steady_clock::time_point time_point;
/* unit time interval definition */
typedef std::chrono::milliseconds time_interval;

/*
 * @ brief A GUI Timer Class
 * @ Detail
 * The class performs 7 actions:
 * open: open up a window and display welcom picture
 * startTiming: start timing from 0s
 * run: print timing in console every 1s, and refresh window every 0.1s
 * stopTiming: stop timing and set time to 0s
 * close: close the window
 * pause: pause timing
 * resume: resume timing from paused time point
 */

class Timer{
	public:
		Timer(const std::string &img);
		void open();
		void startTiming();
		void run();
		void stopTiming();
		void close();
		void pause();
		void resume();
	private:
		std::string image_file;	/*!< string, name of image file*/
		cv::Mat image;			/*!< Mat format image*/
		bool _running = false;	/*!< running flag */
		bool _open = false;		/*!< window open flag*/
		time_point start;		/*!< start time point*/
		time_interval count;	/*!< timing period*/
		
};
#endif  //  TIMER_H
