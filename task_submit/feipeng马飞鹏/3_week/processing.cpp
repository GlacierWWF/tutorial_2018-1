
/***********************************************************************
*
*  
*
*  @file       processing.cpp
*  @brief      识别数码管的主程序
*
*
*  @author     马飞鹏
*  @email      767102280@qq.com
*  @version    1.0.0
*  @date       2018/10/14
*
*
*  ------------------------------------------------------------
*  修改历史：
*  ------------------------------------------------------------
*  <日期>    |  <版本> |  <作者>  |  <描述>
*  ------------------------------------------------------------
*  2018/10/14 |  1.0.0  |  马飞鹏  | 创建文件
*  ------------------------------------------------------------
*  2018/10/15 |  1.0.1  |  马飞鹏  | 修改了导致溢出的bug
*  ------------------------------------------------------------
*/

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<opencv2/ml.hpp>
#include "tell_digital.h"
#include "compare_pic.h"
#include "merg.h"
using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
	Mat src_image,src_image1,src_image2;
	
	src_image1 = imread(argv[1]);//读入原图像
	if(argc==2)
	{
		src_image=src_image1.clone();
	}
	if(argc==3)
	{
		src_image2=imread(argv[2]);
		merg(src_image1,src_image2,src_image);	
	}

	vector<Mat> channels;
	split(src_image,channels);
	Mat R_image = channels.at(2);//提取原图像的R通道，存到R_image中
	equalizeHist(R_image,R_image);
	Mat bin_image,dst_image;
	threshold(R_image,bin_image,220,255,THRESH_TOZERO);
	Mat out_image;
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	erode(bin_image,bin_image,element);
	erode(bin_image,dst_image,element);
	/*****************膨胀找出矩形**********dilate(5,5)x4,dilate(1,5)x2********/
	Mat element_p =getStructuringElement(MORPH_RECT,Size(5,5));
	dilate(dst_image,dst_image,element_p);
	dilate(dst_image,dst_image,element_p);
	dilate(dst_image,dst_image,element_p);
	dilate(dst_image,dst_image,element_p);

	Mat element_k=getStructuringElement(MORPH_RECT,Size(1,5));
	dilate(dst_image,dst_image,element_p);
	dilate(dst_image,dst_image,element_p);

	/**********************************************/
	
	
	/*****************找出轮廓*********************/

	Mat con = Mat::zeros(dst_image.rows,dst_image.cols,CV_8UC3);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(dst_image,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
	for(int index=0;index>=0;index=hierarchy[index][0])
	{
		drawContours(con,contours,index,Scalar(255,255,255),CV_FILLED,8,hierarchy);
	}
	vector<vector<Point>> conpoint_1(contours.size());
	vector<Rect> boundRect_1(contours.size());
	int rect_num =0;
	for(int i=0;i<contours.size();i++)
	{
		approxPolyDP(Mat(contours[i]),conpoint_1[i],3,true);
		boundRect_1[i] = boundingRect(Mat(conpoint_1[i]));
		rect_num++;
	
	}
	vector<Rect> used,used_0;
	int used_rect=0;
	int used_rect_0=0;
	if(rect_num>4)
	{
	for(int i=0;i<rect_num;i++)
	{
		if(boundRect_1[i].width<boundRect_1[i].height&&boundRect_1[i].height>100){
			used_0.push_back(boundRect_1[i]);
			used_rect_0++;
		}	
	}
	for(int i=0;i<used_rect_0;i++)
	{
		if(used_0[i].area()>800)
		{
			used.push_back(used_0[i]);
			used_rect++;
		}
	}
	}
	else
	{
		for(int i=0;i<rect_num;i++)
		{
			used.push_back(boundRect_1[i]);
			used_rect=rect_num;
		
		}
	
	}
	
	rect_num =used_rect;
	for(int i=0;i<used_rect;i++)
	{
		rectangle(src_image,used[i],Scalar(0,255,0),5,0);
	
	}
	/**********************************************/
	sort(used.begin(),used.end(),cmp);
	Mat digital[4];
	for(int i=0;i<rect_num;i++)
	{
		digital[i]=bin_image(used[i]).clone();
	}
	/**********************对单个数字进行识别并输出结果***********************/

	int k;
	for(int i=0;i<4;i++)
	{
		k=tell_num(digital[i]);
		cout<<k<<" ";
	}
	cout<<endl;
	

	/*************************************************************************/
	
	namedWindow("d1",1);
	namedWindow("d2",1);
	namedWindow("d3",1);
	namedWindow("d4",1);
	imshow("d1",digital[0]);
	imshow("d2",digital[1]);
	imshow("d3",digital[2]);
	imshow("d4",digital[3]);

	namedWindow("src",1);
        imshow("src",src_image);
        waitKey(0);
        return 1;
	
	


}
