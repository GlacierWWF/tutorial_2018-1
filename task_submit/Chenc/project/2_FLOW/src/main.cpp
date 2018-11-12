/*
*Title:main.cpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-11-9
*Version:1.0.0
*Abstract: A program to caculate flow
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.hpp>//ust to call the calcOpticalFlowPyrLK fuction
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <ctime>
//caculate FPS
#include "flow.hpp"
using namespace cv;
using namespace std;

int main(void)
{
	Mat image1, image2;
	//vector<Point2f> point1, point2, pointCopy;
	vector<Point> point1, point2, pointCopy;
	vector<uchar> status;
	vector<float> err;
 
	VideoCapture cap;
	Mat frame, frame2;
	cap.open(0);
	cap >> frame; 
	Mat image1Gray, image2Gray;
	cvtColor(frame, image1Gray, CV_RGB2GRAY);
	//namedWindow("dd", 0);
	//imshow("dd", frame);
	
	
	goodFeaturesToTrack(image1Gray, point1, 30, 0.01, 5, Mat()); 
	pointCopy = point1;
	cout<<"The number of keypoints is "<<point1.size()<<endl;
	//Find the some fit points to caculate;
	//the flow.c seguest us to caculate the 4x4 pixel block grand to jude keypoints
	//the result does not seem good 
	int p = 1;
	
	//while(1)
	//{
		for (int i = 0; i<point1.size(); i++)    //draw the keypoints  
		{
		circle(frame, point1[i], 1, Scalar(0, 0, 255), 2);
	
		}
		//imshow("xx", frame);
		//waitKey(0);
	//}
	//cout<<"The average pixel displacement now is : ";
	double fpstime = 1.0;
	while (1)
	{	
		
		
		cap >> frame2;
		cvtColor(frame2, image2Gray, CV_RGB2GRAY);
		//goodFeaturesToTrack(image2Gray, point2, 20, 0.01, 10, Mat()); 
		//if(p % 20 == 0)
		//goodFeaturesToTrack(image1Gray, point1, 20, 0.01, 10, Mat()); 
	
		//initialize point2
		vector<Point> point2(point1.size());			
		double dist = computerSAD(image1Gray,image2Gray,point1,point2);

		if(p%10==0)
		//double a = dist[0]/fpstime;
		//double b = dist[1]/fpstime;
		//double c = dist[2]/fpstime;
		//cout<<"Average pixel flow on x coordinate are "<<a<<endl;
		//cout<<"Average pixel flow on y coordinate are "<<b<<endl;
		{
		cout<<"Average pixel flow now are "<<dist<<endl;
		//cout<<"The point2 detected is "<<point2.size()<<endl;	
		}		

		//***************	
		//calcOpticalFlowPyrLK(image1Gray, image2Gray, point1, point2, status, err, Size(20, 20), 3); //LK金字塔       
		//***************
		//goodFeaturesToTrack(image2Gray, point2, 20, 0.01, 10, Mat());
	
		for (int i = 0; i<point1.size(); i++)
		{
			circle(frame2, point2[i], 1, Scalar(0, 0, 255), 2);
			if(point1[i].x - point2[i].x > 100 || point1[i].y - point2[i].y > 100 || point2[i].x - point1[i].x > 100 || point2[i].y - point1[i].y > 100)
			continue;
			line(frame2, point1[i], point2[i], Scalar(255, 0, 0), 2);
		}

		//time_t start = time(0);
		//double fpstime; 
		imshow("xx", frame2);
		waitKey(10);
		//time_t end = time(0);
		//fpstime = end - start;
		if(p%20 ==0)
		goodFeaturesToTrack(image2Gray, point2, 30, 0.01, 5, Mat());
		swap(point1,point2);
		image1Gray = image2Gray.clone();
		p++;
	}
	return 0;
}


