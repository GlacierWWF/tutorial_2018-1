/*************************************
 *  @file     Timer.hpp
 *  @brief    a basic timer class
 *
 *-------------------------------------
 *  Details.
 *-------------------------------------
 *  @author   HausinLynn
 *  @email    linhx36@mail2.sysu.edu.cn
 *  @version  1.0.0.1
 *  @date     10/02/2018
 *-------------------------------------
 *
 *-------------------------------------
 *  Change History:
 *  <Date>     | <version> | <Author>
 *-------------------------------------
 *  10/02/2018 | 1.0.0.1   | HausinLynn
 *-------------------------------------
 *
 *************************************/

#ifndef TIMER_H
#define TIMER_H

/// System Header
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/* time point of now */
#define Now std::chrono::steady_clock::now()

/* define type of time point */
typedef std::chrono::steady_clock::time_point    timePoint;

/* define type of duration in milliseconds */
typedef std::chrono::milliseconds                millis;

/**
 * @brief	timer class
 *
 * @Detail
 * This is a class which can complete functions of timer,
 * such as starting timing, stoping timing, showing the
 * time, pausing and resuming.
 */
class Timer {
public:
	/**
	 * @brief	constructor
	 */
	Timer(const std::string &img);

	/**
	 * @brief   open a window with an image for time demo
	 *
	 * @note    open is valid only when there is no window.
	 */
	void open();

	/**
	 * @brief	close the time demo window
	 *
	 * @note    close is valid only when there is a window.
	 */
	void close();

	/**
	 * @brief	start timing from zero
	 *
	 * @note    startTiming is valid only when timer is non-working.
	 */
	void startTiming();

	/**
	 * @brief	stop timing
	 *          --timer stops working and time is reset.
	 *
	 * @note	stopTiming is valid only when timer is workin.g
	 */
	void stopTiming();

	/**
	 * @brief	time demo
	 *
	 * @note    --only when timing can it output to terminal.
	 *			--only with the window on can it show in the window.
	 */
	void demoTime();

	/**
	 * @brief	pause timing
	 *          --timer stops working but time isn't reset.
	 *
	 * @note    pause is valid only when timer is working.
	 */
	void pause();

	/**
	 * @brief	resume timing
	 *
	 * @note	resume is valid only when timer is non-working.
	 *			--timer continue working from last count if last
	 *			  operation is pause.
	 *			--timer restart working from zero if last 
	 *			  operation is stop.
	 */
	void resume();

private:
	std::string img_name;	/*!< name of the background image */
	cv::Mat image;			/*!< the background image */
	bool isOpen;			/*!< whether the window is open */
	bool isTiming;			/*!< whether timer is working */
	timePoint startTime;	/*!< start time of each count */
	millis countTime;		/*!< time that has been counted, in milliseconds */
	millis oddTime;			/*!< odd time of a count when pausing */
};

#endif
