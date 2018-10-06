/*****************************************
 *   @file      Timer.cpp
 *   @brief     source file of class Timer
 *   
 *----------------------------------------
 *	 Details.
 *----------------------------------------
 *   @author	HausinLynn
 *   @email		linhx36@mail2.sysu.edu.cn
 *   @version	1.0.0.1
 *   @date		10/02/2018
 *----------------------------------------
 *
 *----------------------------------------
 *   Change History:
 *   <Date>     | <Version> | <Author>
 *----------------------------------------
 *   10/02/2018 | 1.0.0.1   | HausinLynn
 *----------------------------------------
 *
 ****************************************/

/// Class Headers
#include "Timer.hpp"

using namespace std;

/**
 * @brief    constructor
 */
Timer::Timer(const string &img) {
	/* initialzie the timer to a non-working state */
	isTiming = false;
	isOpen = false;

	countTime = millis(0);
	oddTime = millis(0);

	//!< background of GUI
	img_name = img;
	image = cv::imread(img_name);
}

/**
 * @brief    open a window with an image for time demo
 *
 * @note	 open is valid only when there is no window.
 */
void Timer::open() {
	if (!isOpen) {
		cv::namedWindow("Timer", 0);
		cv::resizeWindow("Timer", 400, 700);

		/* show background image */
		cv::imshow("Timer", image);
		cv::waitKey(1);

		isOpen = true;
	}
}

/**
 * @brief	 close the time demo window
 *
 * @note     close is valid only when there is a window.
 */
void Timer::close() {
	if (isOpen) {
		cv::destroyWindow("Timer");
		isOpen = false;
	}
}

/**
 * @brief    start timing from zero
 *
 * @note     startTiming is valid only when timer is non-working.
 */
void Timer::startTiming() {
	if (!isTiming) {
		/* set the timer to a working state */
		isTiming = true;
		
		/* time point of now */
		startTime = Now;
	}

	countTime = millis(0);
	oddTime = millis(0);
}

/**
 * @brief    stop timing
 *           --timer stops working and time is reset.
 *
 * @note	 stopTiming is valid only when timer is working.
 */
void Timer::stopTiming() {
	if (isTiming) {
		/* set the timer to a non-working state */
		isTiming = false;
	}
	
	/* reset time */
	countTime = millis(0);
}

/**
 * @brief    time demo
 *
 * @note     --only when timing can it output to terminal.
 *		     --only with the window on can it show in the window.
 */
void Timer::demoTime() {
	if (isTiming) {    // if timer is working
		timePoint presentTime = Now;
		millis duration = chrono::duration_cast<millis>(presentTime - startTime);
		
		/* count on every 100 milliseconds */
		if (duration.count() > millis(100).count()) {
			startTime = Now;
			countTime += millis(100);

			/* output to terminal per seconds */
			if (countTime.count() % 1000 == 0) 
				cout << countTime.count() / 1000 << endl;
		} 
	}
	
	if (isOpen) {
		/*!< counted time in milliseconds */	
		double millis_count = countTime.count() / 1000.0;
		
		/* get the string form of time */
		stringstream msg_stream;
		string count_msg;
		msg_stream << "Time: " << millis_count << "s";
		count_msg = msg_stream.str();
		
		int font_face						/*!< font face */
		   	= cv::FONT_HERSHEY_COMPLEX;
		double font_scale = 2;				/*!< font scale */
		int thickness = 2;					/*!< thickness */
		int baseline;							
		cv::Size text_size = cv::getTextSize
			(count_msg, font_face, font_scale, thickness, &baseline);

		cv::Point origin;					/*!< origin */
		origin.x = image.cols / 2 - text_size.width / 2;
		origin.y = image.rows * 5 / 6;

		cv::Scalar color(255, 0, 0);		/*!< color */
		
		cv::putText(image, count_msg, origin, font_face, font_scale,
			   	color, thickness, 8, false);
		
		/* update image */
		cv::imshow("Timer", image);
		image = cv::imread(img_name);
		cv::waitKey(1);
	}
}

/**
 * @brief    pause timing
 *			 --timer stops working but time isn't reset.
 *
 * @note     pause is valid only when timer is working.
 */
void Timer::pause() {
	if (isTiming) {
		/* set the timer to a non-working state */
		isTiming = false;
		
		/* store odd time */
		timePoint presentTime = Now;
		oddTime = chrono::duration_cast<millis>(presentTime - startTime);
	}
}

/**
 * @brief	resume timing
 *          --timer continue working if last operation is pause.
 *          --timer restart working if last operation is stop.
 *
 * @note    resume is valid only when timer is non-working.
 */
void Timer::resume() {
	if (!isTiming) {
		/* reset the timer to a working state */
		isTiming = true;
		
		/* start time with consideration about add time */
		startTime = Now + oddTime;
	}
}
