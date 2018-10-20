/*Title:LEDdetect.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-10-15
*Version:1.0.0
*Abstract: A program using KNN to distinguish the LED-numbers
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <iostream>
#include "Degree.hpp"
#include "Process.hpp"

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	char *imgName1 = argv[1];
	string imgName = imgName1;
	//convert the char* to string;
	Mat image,gray_img;
	image = imread(imgName, 1);	

	cv::namedWindow("Image",CV_NORMAL);
	cv::imshow("Image",image);//show image
	cv::waitKey(0);
	
	int _threshold;
	int dil_kernel,blur_kernel;
	bool ifGamma,isRecify;
	int cmin,cmax;
	int w1_low = 10, w1_high = 40;    // width boundary for number "1"
	int w2_low = 55, w2_high = 100;   // width boundary for othe numbers
	int h_low = 100, h_high = 160;
    	if (argc == 2)
    	{
	    	
		if(image.rows == 180)//simple_samples
		{
			simple(image,gray_img,ifGamma);
			_threshold = 120;
			if(ifGamma)
				dil_kernel = 11;
			else
				dil_kernel = 7;
			blur_kernel = 11;
	
		}
		else//actual_samples
		{
			actual(image,gray_img,isRecify);
			_threshold = 200;
			dil_kernel = 13;
			blur_kernel = 5;
	
		}
		
	}
    	if (!image.data)
    	{
		cout << "No image data" << endl;
        	return -1;
  	}

	Mat binary_img;
 	threshold(gray_img,binary_img,_threshold,255.0,CV_THRESH_BINARY);
	cv::namedWindow("Binary_Image",CV_WINDOW_NORMAL);
	cv::imshow("Binary_Image",binary_img);//show binaryimage   
	cv::waitKey(0);
	
	Mat erode_img,dilate_img;
	Mat element;
	element = getStructuringElement(MORPH_RECT,Size(dil_kernel,dil_kernel));
 
/*
	erode(binary_img,erode_img,element);
	namedWindow("Erode_Image",CV_WINDOW_AUTOSIZE);
	imshow("Erode_Image",erode_img);//show erodeimage 
*/

	dilate(binary_img,dilate_img,element);
	cv::namedWindow("Dilate_Image",CV_WINDOW_NORMAL);
	cv::imshow("Dilate_Image",dilate_img);//show dilateimage
	cv::waitKey(0);

	Mat Gaussblur_img;
	GaussianBlur(dilate_img,Gaussblur_img,Size(blur_kernel,blur_kernel),0);
	cv::namedWindow("Gaussblur_Image",CV_WINDOW_NORMAL);
	cv::imshow("Gaussblur_Image",Gaussblur_img);
	cv::waitKey(0);

	Mat edge_img;
	Canny(Gaussblur_img,edge_img,50,200);
	cv::namedWindow("edge_Image",CV_WINDOW_NORMAL);
	cv::imshow("edge_Image",edge_img);


	vector< vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(edge_img, contours_out, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
	vector<RotatedRect> minRects(contours_out.size());
	Mat imageContours = Mat::zeros(edge_img.size(), CV_8UC1);
	Mat Contours = Mat::zeros(dilate_img.size(), CV_8UC1);//
	
	/*vector<std::vector<cv::Point> >::iterator itc = contours_out.begin();
	while (itc != contours_out.end())
	{
		if (itc->size() < cmin || itc->size() > cmax)
			itc = contours_out.erase(itc);
		else
			++itc;
	}
	//find the contours needed
	*/	
	std::cout <<"number of contours is: "<< contours_out.size() << endl;
	vector<Rect> numbers,contours;
	for(int i = 0;i< contours_out.size();i++)
	{
		Rect rect1 = boundingRect(Mat(contours_out[i]));
		//
		int width,height;
		width = rect1.width;
		height = rect1.height;
		contours.push_back(rect1);
		if(image.rows == 180)//simple_samples
		{
			if((width >= 10&&width <= 40|| width >= 60 && width <= 100) && (height >= 100 && height <= 160))
			numbers.push_back(rect1);
		}
		else if(image.rows == 600)//act_samples
		{
			if((width >= 10&&width<=40 ||width >=54 && width<=100) && (height >=95 && height<=160))
			numbers.push_back(rect1);
		}
	}
	sort(numbers.begin(),numbers.end(),cmp);

	for(int i = numbers.size();i>0;i--)
	{
		if (numbers[i].width == numbers[i-1].width && numbers[i].height == numbers[i-1].height)
			{
				if(numbers[i].x-numbers[i-1].x<10)
					numbers.erase(numbers.begin()+i);
			}
	}
	

	Mat number_img;
	number_img = image.clone();
	cout<<"The number detected: "<<numbers.size()<<endl;

	int amount = 0;
	vector<Mat> LED;
	for(int i = 0;i<numbers.size();i++)
	{
	
		rectangle(number_img,numbers[i],(255,0,0),8,8,0);
		
	}
	cv::namedWindow("Numbers_image",CV_WINDOW_NORMAL);
	cv::imshow("Numbers_image",number_img);
	cv::waitKey(0);


	for(int i = 0;i<numbers.size();i++)
	{
		LED.push_back(dilate_img(numbers.at(i)));
		string  Img_Name = "data/output/" + std::to_string(i+1) + ".jpg";
		imwrite(Img_Name, LED.at(amount));
		amount = amount + 1;
	}

	//Rect rect1 = boundingRect(Mat(contours_out[i]));
	//	cv::Mat imageROI;
		//int cols = number_img.cols, number_img = img.rows;
		//if (cols - 1 - rect.x<rect.width || rows - 1 - rect.y<rect.height)
		//	return -1;
	//	imageROI = number_img(rect1(rect1.x, rect1.y, rect1.width, rect1.height));
		//imshow("SignROI", img);
		//dilate_img.copyTo(img);  
		//imshow("ROI", imageROI);
	//	string  Img_Name = "data/output/" + std::to_string(i) + ".jpg";
	//	imwrite(Img_Name, imageROI);

	//for(int i = contours_out.size()-1;i>=0; i--)
	//{
		
		//minRects[i] = minAreaRect(Mat(contours_out[i]));
		
		//Point2f rectPoints[4];
		//minRects[i].points(rectPoints);
		//if(minRects[i].x > minRects[i+1].x)
		//for (int j = 0; j < 4; j++)
		//{
		//	line(imageContours, rectPoints[j], rectPoints[(j + 1) % 4], Scalar(255), 1.5, CV_AA, 0);
		//}
		//Rect rect = minRects[i].boundingRect();
		//cv::Mat imageROI;
		//cv::Mat img;
		//dilate_img.copyTo(img);
		//int cols = img.cols, rows = img.rows;
		//ROIÔœœç£¬·µ»Ø
		//if (cols - 1 - rect.x<rect.width || rows - 1 - rect.y<rect.height)
		//	return -1;
		//imageROI = img(Rect(rect.x, rect.y, rect.width, rect.height));
		//rectangle(img, rect, Scalar(0, 0, 255), 2);
		//imshow("SignROI", img);
		//dilate_img.copyTo(img); 
		//imshow("ROI", imageROI);
		
		//cv::namedWindow("contours_Image", CV_WINDOW_AUTOSIZE);
		//cv::imshow("contours_Image", imageContours);//show dilateimage
		//cv::waitKey(1);
		
		//string  Img_Name = "data/output/" + std::to_string(4-i) + ".jpg";
		//imwrite(Img_Name, imageROI);
	//}
	
	//cv::namedWindow("contours_Image",CV_WINDOW_AUTOSIZE);
	//cv::imshow("contours_Image",imageContours);//show dilateimage
	//cv::waitKey(1);

	const int K = 3;
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);

        //const std::string image_path{ "./data/" };
	cv::Mat tmp_unify= cv::imread("data/sample1/0/0_ (1).jpg", 0);
	threshold(tmp_unify, tmp_unify, 50, 255, THRESH_BINARY);
	cv::Mat tmp(Size(40,60), CV_32FC1, Scalar(0));	
	cv::resize(tmp_unify, tmp, Size(40,60), 0, 0, INTER_LINEAR);

	const int train_samples_number = 100;
	const int predict_samples_number = 4;
	const int every_class_number = 10;

	cv::Mat train_data(train_samples_number, tmp.rows * tmp.cols, CV_32FC1);
	cv::Mat train_labels(train_samples_number, 1, CV_32FC1);
	float* p = (float*)train_labels.data;
	for (int i = 0; i < 10; ++i) {
		std::for_each(p + i * every_class_number, p + (i + 1)*every_class_number, [i](float& v) {v = (float)i; });
	}

	// train data
	for (int i = 0; i < 10; ++i) {
		static const std::vector<std::string> digit = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", };
		static const std::string suffix = { ".jpg" };
		for (int j = 1; j <= every_class_number; ++j) {
			std::string image_name = "data/sample1/" + digit[i] + "/" + digit[i] +"_ ("+std::to_string(j) + ")" + suffix;
			//E:\\sample\\0\\0_ (1).jpg
			cv::Mat image_undifinedsize = cv::imread(image_name, 0);
			threshold(image_undifinedsize, image_undifinedsize, 50, 255, THRESH_BINARY);
			cv::Mat image1(Size(40, 60), CV_32FC1, Scalar(0));
			cv::resize(image_undifinedsize, image1, Size(40, 60), 0, 0, INTER_LINEAR);
			//cv::namedWindow("Image1", CV_WINDOW_AUTOSIZE);
			//cv::imshow("Image1", image1);
			//waitKey(1);
			//CHECK(!image1.empty() && image1.isContinuous());
			image1.convertTo(image1, CV_32FC1);//×ª»»žñÊœ
			image1 = image1.reshape(0, 1);//ÉèÖÃ³Éµ¥ÐÐ
			tmp = train_data.rowRange(i * every_class_number + j - 1, i * every_class_number + j);
			image1.copyTo(tmp);//œ«image1žŽÖÆµœtmpÖÐ 
		}
	}
	knn->train(train_data, cv::ml::ROW_SAMPLE, train_labels);
	// predict data
	cv::Mat predict_data(predict_samples_number, tmp.rows * tmp.cols, CV_32FC1);
		static const std::string suffix = { ".jpg" };
		for (int j = 1; j <= 4; ++j) {
			std::string image_name = "data/output/" + std::to_string(j) +  suffix;
			cv::Mat image2 = cv::imread(image_name, 0);
			cv::Mat image3(Size(40, 60), CV_32FC1, Scalar(0));
			cv::resize(image2, image3, Size(40, 60), 0, 0, INTER_LINEAR);
		
			string  Img_Name1 = "data/50*50size/" + std::to_string(j) + ".jpg";
			imwrite(Img_Name1, image3);
			//CHECK(!image3.empty() && image3.isContinuous());
			image3.convertTo(image3, CV_32FC1);
			image3 = image3.reshape(0, 1);

			tmp = predict_data.rowRange(j - 1, j );
			image3.copyTo(tmp); 
		}
	cv::Mat result;
	knn->findNearest(predict_data, K, result);
	//CHECK(result.rows == predict_samples_number);

	cv::Mat predict_labels(predict_samples_number, 1, CV_32FC1);
	p = (float*)predict_labels.data;
	for (int i = 1; i <= 4; ++i) {
		std::for_each(p + i, p + (i + 1), [i](float& v) {v = (float)i; });
	}
	int number;
	cout<<"The LED numbers is"<<endl;
	for (int i = 0; i < predict_samples_number; ++i) {

		float value2 = ((float*)result.data)[i];
		cout << value2;
	}
	std::cout<<endl;
	waitkey(1);
 return 0;
}
