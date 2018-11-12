/*Title:LEDdetect.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-11-8
*Version:1.0.0
*Abstract: A program to realize the SIFT keypoints matching algorithm
*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "sift.hpp"
 
 
using namespace std;
using namespace cv;
 
int main(int argc, char **argv)
{
	cv::Mat src1 = cv::imread("data/4.jpg");
	cv::Mat src2 = cv::imread("data/5.jpg");
	cv::resize(src1,src1,Size(450,600) ,0, 0, INTER_LINEAR);
	cv::resize(src2,src2,Size(450,600) ,0, 0, INTER_LINEAR);
	Size size(src1.cols+src2.cols,MAX(src1.rows,src2.rows));
	cv::Mat src;
	src.create(size,src1.type());
	//combine two pictures
	//src1.colRange(0,src1.cols).copyTo(src.colRange(0,src1.cols));
	Mat src1_out,src2_out;
	src1_out = src(Rect(0,0,src1.cols,src1.rows));
	src2_out = src(Rect(src1.cols,0,src2.cols,src2.rows));
	src1.copyTo(src1_out);
	src2.copyTo(src2_out);	
	//src2.colRange(0,src2.cols).copyTo(src.colRange(src1.cols+1,src.cols));
	//imshow("CombinePicture",src); 
	if(src1.empty() || src2.empty())
	{
		cout << "image open error! "<<endl;
		getchar();
		return -1;
	}
	if(src1.channels()!=3 || src2.channels()!=3)  return -2;
 
	vector<Keypoint> features1;
 	vector<Keypoint> features2;

	//detect the keypoints and descriptors
	Sift(src1, features1, 1.6);                       
	Sift(src2, features2, 1.6);

 	//DrawKeyPoints(src1, features1);       
	//DrawKeyPoints(src1, features1); 
	
	DrawSiftFeatures(src1, features1);                  
	DrawSiftFeatures(src2, features2); 
	cv::imshow("image1", src1);
	cv::imshow("image2", src2);

	//match the keypoints
	FindMatching(src,src1,src2,features1,features2,300);
	cv::imshow("FinalMatch", src);

	//write the keypoints into txt file
	//write_features(features1, "descriptor1.txt");
	//write_features(features2, "descriptor2.txt");
 
	waitKey(0);
 
	return 0;
}


