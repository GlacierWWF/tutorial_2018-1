/* Title: Timer.cpp
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-10-06
 * Version: 1.0.0
 * Abstract: Implementation of Timer class
 */
#include "Timer.hpp"

using namespace cv;
using namespace std;

Timer::Timer(const string &img){
	image_file = img;
	image = imread(image_file);
	if (image.data == NULL) cout << "read image failed" << endl;
	count = time_interval(0);
}

void Timer::open(){
	if (!_open){
		namedWindow("Timer", 0);
		resizeWindow("Timer", 1071, 621);
		imshow("Timer", image);
		waitKey(1);
		_open = true;
	}
}

void Timer::startTiming(){
	if (!_running){
		start = std::chrono::steady_clock::now();
		_running = true;
	}
	count = time_interval(0);	
}

void Timer::run(){
	if (_running){
		time_point present = chrono::steady_clock::now();
        time_interval timing = chrono::duration_cast<time_interval>(present - start);

       		if (timing.count() > time_interval(100).count()){
                	start = chrono::steady_clock::now();
                	count += time_interval(100);

                	if (count.count() % 1000 == 0)
                        	cout << count.count() / 1000 << endl;

		}
	}
	
	if (_open){
		double seconds = count.count() / 1000.0;

		stringstream msg_stream;
		string count_msg;
		msg_stream << "Time: " << seconds << " s";
		count_msg = msg_stream.str();

		int font_face = FONT_HERSHEY_SIMPLEX;
		double font_scale = 4;
		int thickness = 2;
		int baseline;
		cv::Size text_size = cv::getTextSize
			(count_msg, font_face, font_scale, thickness, &baseline);
		cv::Point origin;
		origin.x = image.cols/2 - text_size.width/2;
		origin.y = image.rows*5/6;
		cv::Scalar color(255, 255, 255);

		cv::putText
			(image, count_msg, origin, font_face, font_scale,
			 color, thickness, 8, false);
		cv::imshow("Timer", image);
		image = cv::imread(image_file);
		cv::waitKey(1);
	}
}

void Timer::stopTiming(){
	if (_running){
		_running = false;
	}
	count = time_interval(0);
}

void Timer::close(){
	if(_open){
		destroyWindow("Timer");
		_open = false;
	}
}

void Timer::pause(){
	if (_running){
		_running = false;
		time_point present = std::chrono::steady_clock::now();
	}
}

void Timer::resume(){
	if (!_running){
		_running = true;
	}
}

