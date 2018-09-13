#include <iostream>
#include <opencv2/opencv.hpp>
#include <atomic>
#include <thread>
#include <vector>
#include <time>

using namespace std;
using namespace cv;

double rgb_w[] = {1.00, 0.05, 0.05, 1.00};

void process(const Mat& input, Mat& output)
{
	Mat pic;
	vector<Mat> bgr;
	split(input, bgr);

	/*
	pic = bgr[0] * rgb_w[2] + bgr[1] * rgb_w[1] + bgr[2] * rgb_w[0] + rgb_w[3];
	cv::threshold(pic, pic, 128, 255, CV_THRESH_BINARY);
	*/

	Mat kernel = cv::getStructuringElement(MORPH_RECT, Size(3,3));
	pic = bgr[0] * rgb_w[2] + bgr[1] * rgb_w[1] + bgr[2] * rgb_w[0] + rgb_w[3] > 127;
	morphologyEx(pic, pic, MORPH_OPEN, kernel);
	morphologyEx(pic, pic, MORPH_CLOSE, kernel);

	output = pic.clone();
}

int main(int argc, char** argv)
{
	string pathname;
	if(argc > 1)
		pathname = argv[1];

	cv::Mat img;
	img = cv::imread(pathname);
	cv::namedWindow("origin");
	cv::imshow("origin", img);
	waitKey(0);

	cv::Mat pcs;
	process(img, pcs);
	cv::namedWindow("process");
	cv::imshow("process", pcs);
	waitKey(0);

	return 0;
}
