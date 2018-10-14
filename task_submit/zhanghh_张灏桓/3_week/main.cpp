//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_14
//Version:v1.0.0
//Abstract:Read the number from pixel_cube.

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <ratio>
#include <pthread.h>
#include <math.h>
#include <cstdlib>
#include<opencv2/opencv.hpp>
#pragma comment(lib,"opencv_world330.lib")
#include "nixie.cpp"
using namespace cv;
using namespace std;
using namespace std::chrono;





int main( int argc, char** argv )
{
	string load_path;
	IplImage *ori_image;
	cout << "Please input the path of image, sperate by space." << endl;
	getline(cin, load_path);

	int space_index = load_path.find(" ");
	cout << space_index << endl;
	if(space_index == -1)
	{
		if(load_path.find("sim"))
			cout << "sim_sample" << endl;
		else
			cout << "act_simple" << endl;
		const char *path = load_path.data();
		ori_image = cvLoadImage(path, 1); 
	}
	else
	{
		cout << "hard_sample" << endl;
		stringstream ss(load_path);
		string pathstr1, pathstr2;
	       	ss >> pathstr1;
		ss >> pathstr2;
		const char *path1 = pathstr1.c_str(), *path2 = pathstr2.c_str();
		IplImage *image_1 = cvLoadImage(path1, 1);
		IplImage *image_2 = cvLoadImage(path2, 1);
		Mat M1 = cvarrToMat(image_1);
		Mat M2 = cvarrToMat(image_2);
		Mat dst;
		addWeighted(M1, 0.6, M2, 0.6, 0, dst);
		IplImage temp_image = dst;
		ori_image = cvCloneImage(&temp_image);
	}

	if (cvarrToMat(ori_image).empty()) // read RGB image 
		return -1;
	imshow("image_ori", cvarrToMat(ori_image)); 


	IplImage *redImage = cvCreateImage(cvGetSize(ori_image), IPL_DEPTH_8U,1); 
	IplImage *greenImage = cvCloneImage(redImage);
	IplImage *blueImage = cvCloneImage(redImage);
	IplImage *image_lap = cvCloneImage(redImage);

	cvSplit(ori_image, redImage, greenImage, blueImage, NULL);

	//imshow("image_red", cvarrToMat(redImage)); // read RGB image 
	//imshow("image_green", cvarrToMat(greenImage)); // read RGB image 
	//imshow("image_blue", cvarrToMat(blueImage)); // read RGB image 

 
	Mat image_gry = cvarrToMat(blueImage);
	Mat image_eql;
	imshow("image_gry", image_gry);
	Mat image_gau;
  
	Mat image_thr;
	threshold(image_gry, image_thr, 182, 255, THRESH_BINARY); // convert to binary image
	//imshow("image_thr", image_thr);
	GaussianBlur(image_thr, image_gau, Size(5,5),0,0);
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(14, 14)); // expend
		dilate(image_gau, image_dil, element);
	//imshow("image_dil", image_dil);
	threshold(image_dil, image_dil, 65, 255, THRESH_BINARY); // binaryzation
	imshow("image_dil", image_dil); 


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(image_dil, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE); // find the edge of number
	
	//imshow("loaction", image_thr);
	//imshow("image_dil2", image_dil);
	

	const size_t size = contours.size();
	vector<Rect> num_location;
	for (int i = 0; i < contours.size(); i++)
	{
		num_location.push_back(boundingRect(Mat(contours[i])));
	}
	sort(num_location.begin(), num_location.end(), cmp);  // adjust location


	char rectnum[255];
	char filenamew[255];
	int tube_num = 0;
	//sprintf(filenamew, "loaction");
	vector<Mat> tube; 
	
	for (int i = 0; i < contours.size(); i++)
	{
		if (!White_noise(image_dil(num_location.at(i))) && test_numebr(image_dil(num_location.at(i))) != -1)
		{
			cv::rectangle(image_thr, num_location.at(i).tl(),num_location.at(i).br(), Scalar(255, 0, 0), 1, 1, 0);
			tube.push_back(image_dil(num_location.at(i)));
			tube_num++;
		}
	}

	imshow("image_thr", image_thr);

	string ans = "";
	cout << tube_num << endl;

	for (int i = 0; i < tube_num; i++)
	{
		cout << "tube:" << i << endl;
		int number = test_numebr(tube.at(i));
		cout << number << endl;
		if(number > -1)
		ans += ('0' + number);
	}
	cout << "ANSWER: " << ans << endl;
	waitKey(0);
	destroyAllWindows();
	return 0;
}

 

