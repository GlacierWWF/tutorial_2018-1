/*Title:IP.hpp
*Author:Chen Ruijia
*Revised:Chen Ruijia
*Date:2018-10-15
*Version:1.0.0
*Abstract: A program to detect the LED-numbers
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

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: opencv_test <image path>" << endl;
        return -1;
    }

    char *imgName = argv[1];
    Mat image;
    image = imread(imgName, 1);
    if (!image.data)
    {
        cout << "No image data" << endl;
        return -1;
    }
    Mat gray_img;
    cvtColor(image, gray_img, CV_BGR2GRAY);
    //namedWindow("Gray_Image",CV_WINDOW_AUTOSIZE);
    //imshow("Gray_Image",gray_img);//show grayimage
    Mat binary_img;
    threshold(gray_img,binary_img,50,255.0,CV_THRESH_BINARY);
    //namedWindow("Binary_Image",CV_WINDOW_AUTOSIZE);
    //imshow("Binary_Image",binary_img);//show binaryimage   
    Mat erode_img,dilate_img;
    Mat element;
    element = getStructuringElement(MORPH_RECT,Size(10,10));
/*
    erode(binary_img,erode_img,element);
    namedWindow("Erode_Image",CV_WINDOW_AUTOSIZE);
    imshow("Erode_Image",erode_img);//show erodeimage 
*/
    dilate(binary_img,dilate_img,element);
    namedWindow("Dilate_Image",CV_WINDOW_AUTOSIZE);
    imshow("Dilate_Image",dilate_img);//show dilateimage


    vector< vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(dilate_img, contours_out, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
	vector<RotatedRect> minRects(contours_out.size());
	Mat imageContours = Mat::zeros(dilate_img.size(), CV_8UC1);
	Mat Contours = Mat::zeros(dilate_img.size(), CV_8UC1);  //»æÖÆ 

	//³ýÈ¥Ì«³€»òÕßÌ«¶ÌµÄÂÖÀª   
	int cmin = 300;
	int cmax = 1000;
	vector<std::vector<cv::Point> >::iterator itc = contours_out.begin();
	while (itc != contours_out.end())
	{
		if (itc->size() < cmin || itc->size() > cmax)
			itc = contours_out.erase(itc);
		else
			++itc;
	}
	//¶Ôcontours_outœøÐÐ×ø±êÅÅÐò
	for (int i = contours_out.size()-1; i >=0; i--)
	{
		
		minRects[i] = minAreaRect(Mat(contours_out[i]));//·µ»ØÀàÐÍÎªRotateRect¶ÔÏó£¬²ÎÊýÎªvector<vector<Point>>µãŒ¯£¬×÷ÓÃÎªŒÆËã°üÎ§µãŒ¯µÄ×îÐ¡Ðý×ªŸØÕó
		drawContours(imageContours, contours_out, i, Scalar(255), 1, 20, hierarchy, 0, Point(0, 0));
		Point2f rectPoints[4];//¶šÒåÇÐžîŸØÐÎµÄËÄžö¶¥µã£»
		minRects[i].points(rectPoints);
		//if(minRects[i].x > minRects[i+1].x)
		for (int j = 0; j < 4; j++)
		{
			line(imageContours, rectPoints[j], rectPoints[(j + 1) % 4], Scalar(255), 1.5, CV_AA, 0);
			//cv::namedWindow("contours_Image", CV_WINDOW_AUTOSIZE);
			//cv::imshow("contours_Image", imageContours);//show dilateimage
			//cv::waitKey(1);
		}
		Rect rect = minRects[i].boundingRect();
		cv::Mat imageROI;
		cv::Mat img;
		dilate_img.copyTo(img);
		int cols = img.cols, rows = img.rows;
		//ROIÔœœç£¬·µ»Ø
		if (cols - 1 - rect.x<rect.width || rows - 1 - rect.y<rect.height)
			return -1;
		imageROI = img(Rect(rect.x, rect.y, rect.width, rect.height));
		rectangle(img, rect, Scalar(0, 0, 255), 2);
		//imshow("SignROI", img);
		dilate_img.copyTo(img);    //ROIºÍËüµÄžžÍŒÏñÖžÏòÍ¬Ò»¿é»º³åÇø£¬Ÿ­ŽÎ²Ù×÷Ïû³ý ±êŒÇROIµÄŸØÐÎ¿ò
		//imshow("ROI", imageROI);
		
		//cv::namedWindow("contours_Image", CV_WINDOW_AUTOSIZE);
		//cv::imshow("contours_Image", imageContours);//show dilateimage
		//cv::waitKey(1);
		string  Img_Name = imagename + std::to_string(4-i) + ".jpg";
		imwrite(Img_Name, imageROI);
	}
	std::cout << contours_out.size() << endl;
	//cv::namedWindow("contours_Image",CV_WINDOW_AUTOSIZE);
	//cv::imshow("contours_Image",imageContours);//show dilateimage
	//cv::waitKey(1);

	const int K = 3;
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	//
        //const std::string image_path{ "./data/" };
	cv::Mat tmp_unify= cv::imread(imgName + "/data/sample1/0/0_ (1).jpg", 0);
	cv::Mat tmp(Size(50,50), CV_32FC1, Scalar(0));
	cv::resize(tmp_unify, tmp, Size(50,50), 0, 0, INTER_LINEAR);
	//cv::namedWindow("50*50Image",CV_WINDOW_AUTOSIZE);
	//cv::imshow("50*50Image",tmp);//show dilateimage
	cv::waitKey(1);

	const int train_samples_number = 200;//ÓÃÀŽÑµÁ·µÄÑù±Ÿ
	const int predict_samples_number = 4;//ÐèÒªÔ€²âµÄÊý×Ö
	const int every_class_number = 20;

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
			std::string image_name = imgName + "/data/sample1/" + digit[i] + "/" + digit[i] +"_ ("+std::to_string(j) + ")" + suffix;
			//E:\\sample\\0\\0_ (1).jpg
			cv::Mat image_undifinedsize = cv::imread(image_name, 0);

			cv::Mat image1(Size(50, 50), CV_32FC1, Scalar(0));
			cv::resize(image_undifinedsize, image1, Size(50, 50), 0, 0, INTER_LINEAR);
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
	//for (int i = 0; i < 4; ++i) {
		//static const std::vector<std::string> digit{ "1", "2", "3", "4" };
		static const std::string suffix = { ".jpg" };
		for (int j = 1; j <= 4; ++j) {
			std::string image_name = imgName + "/data/output"/ + std::to_string(j) +  suffix;
			cv::Mat image2 = cv::imread(image_name, 0);
			cv::Mat image3(Size(50, 50), CV_32FC1, Scalar(0));
			cv::resize(image2, image3, Size(50, 50), 0, 0, INTER_LINEAR);
		
			string  Img_Name1 = imgName+"/data/50*50size/" + std::to_string(j) + ".jpg";
			imwrite(Img_Name1, image3);
			//CHECK(!image3.empty() && image3.isContinuous());
			image3.convertTo(image3, CV_32FC1);
			image3 = image3.reshape(0, 1);

			tmp = predict_data.rowRange(j - 1, j );
			//»ñÈ¡ÖÆ¶š·¶Î§µÄÐÐµÄÖžÕë
			image3.copyTo(tmp);//œ«image1žŽÖÆµœtmpÖÐ 
		}
	//}
	cv::Mat result;
	knn->findNearest(predict_data, K, result);
	//CHECK(result.rows == predict_samples_number);

	cv::Mat predict_labels(predict_samples_number, 1, CV_32FC1);
	p = (float*)predict_labels.data;
	for (int i = 1; i <= 4; ++i) {
		std::for_each(p + i, p + (i + 1), [i](float& v) {v = (float)i; });
	}
	int number;
	for (int i = 0; i < predict_samples_number; ++i) {

		float value2 = ((float*)result.data)[i];
		cout << value2;
	}
 return 0;
}
