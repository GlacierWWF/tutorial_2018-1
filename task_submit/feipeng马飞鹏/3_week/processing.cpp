#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<opencv2/ml.hpp>
#include "tell_digital.h"
#include "compare_pic.h"
using namespace std;
using namespace cv;


	
int main(int argc,char **argv)
{
	Mat src_image;
	
	src_image = imread(argv[1]);//读入原图像
	int row_num=src_image.rows;
	int col_num=src_image.cols;
	/********************降噪处理*******************/
	/*
	int row_num=src_image.rows;
	int col_num=src_image.cols;
	for(int i =0;i<row_num;i++)
	{
		for(int j=0;j<col_num;j++)
		{
		if(src_image.at<Vec3b>(i,j)[0]>240&&src_image.at<Vec3b>(i,j)[1]>240)
		{
			src_image.at<Vec3b>(i,j)[0]=0;
			src_image.at<Vec3b>(i,j)[1]=0;
			src_image.at<Vec3b>(i,j)[2]=0;
		}
		}
	}
	*/
	/***********************************************/


	/********************漫水填充处理背景******************/
/*	
	Rect rect;
	floodFill(src_image,Point(1,1),Scalar(0,0,0),&rect,Scalar(5,5,5),Scalar(5,5,5));
*/
	/*****************************************************/

	vector<Mat> channels;
	split(src_image,channels);
	Mat R_image = channels.at(2);//提取原图像的R通道，存到R_image中
//	medianBlur(R_image,R_image,5);
	/*
	 * 也许可以处理一下  R_image.convertTo(R_image,-1,1,15);
	 */
	equalizeHist(R_image,R_image);
	Mat bin_image,dst_image;
	threshold(R_image,bin_image,220,255,THRESH_TOZERO);
	//得到二值化后的图像bin_image
	
	Mat out_image;
	//接下来对二值化后的图像进行滤波处理
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	erode(bin_image,bin_image,element);
	erode(bin_image,dst_image,element);
	//dilate(bin_image,bin_image,
	//分割图像	
	

	/*****************膨胀找出矩形******************/
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
	findContours(dst_image,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
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
//		if(boundRect_1[i].area()>17000)
//			boundRect_1[i]+=Size(-45,0);
		rect_num++;
	
	}
/*
	for(int i=0;i<rect_num;i++)
	{
		if(boundRect_1[i].area()<5000||boundRect_1[i].area()<1000||boundRect_1[i].area()>13000)
			boundRect_1.erase(boundRect_1.begin()+i);
	
	}
*/	
/*	while(iter!=boundRect_1.end())
	{
		if((*iter).area()>14000||(*iter).area()<3000)
			iter = boundRect_1.erase(iter);
		else
			++iter;
		
	}*/
/*
	for(int i=0;i<rect_num;i++)
	{
		if((double)boundRect_1[i].height/boundRect_1[i].width<1.4)
		{

			boundRect_1[i]+=Size(-45,0);
		}
	
	}
	*/
	vector<Rect> used,used_0;
	int used_rect=0;
	int used_rect_0=0;
	if(rect_num>4)
	{
	for(int i=0;i<rect_num;i++)
	{
	/*	if((double)boundRect_1[i].height/boundRect_1[i].width>2.8&&(double)boundRect_1[i].height/boundRect_1[i].width<3.5&&boundRect_1[i].area()<3000)
		{
			
			used.push_back(boundRect_1[i]);
			used_rect++;
		}*/
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


	/****************根据轮廓截取数字部分 粗提取********************
	threshold(con,con,100,255,THRESH_BINARY);	
	int row_middle = con.rows/2;
	int col_middle = con.cols/2;
	int top,botton,left,right;
	int top_times=0;
	int botton_times=0;
	for(int i=row_middle-1;i>0;i--)
	{
		int j=1;
		for(j=1;j<col_num;j++)
		{
			if(con.at<uchar>(i,j)==255)
				break;
			
		}
		if(j==col_num)
		{
			top=i;
			break;
		}
	}


	for(int i=row_middle+1;i<row_num;i++)
	{
		int j=1;
		
		for(j=1;j<col_num;j++)
		{
			if(con.at<uchar>(i,j)==255)
				break;
			
		}
		if(j==col_num)
		{
			botton=i;
			break;
		}
	}
	*******************************************************/




	/*******************从ROI区域提取并框出4个数字**********************/
/*
	Mat element_3=getStructuringElement(MORPH_RECT,Size(3,5));
	dilate(digital_part,digital_part,element_3);
	dilate(digital_part,digital_part,element_3);
	dilate(digital_part,digital_part,element_3);
	dilate(digital_part,digital_part,element_3);
	Mat digital_rect = Mat::zeros(dst_image.rows,dst_image.cols,CV_8UC3);
	vector<vector<Point>> contours_2;
	vector<Vec4i> hierarchy_2;
	findContours(digital_part,contours_2,hierarchy_2,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	for(int index=0;index>=0;index=hierarchy_2[index][0])
	{
		drawContours(digital_rect,contours_2,index,Scalar(255,255,255),1,8,hierarchy_2);
	}
	Mat digital_1,digital_2,digital_3,digital_4;
	vector<vector<Point>> conpoint(contours_2.size());
	vector<Rect> boundRect(contours_2.size());
	int rect_nums=0;
	for(int i=0;i<contours_2.size();i++)
	{
		approxPolyDP(Mat(contours_2[i]),conpoint[i],3,true);
		boundRect[i] = boundingRect(Mat(conpoint[i]));
		if(boundRect[i].area()>17000)
		{
			boundRect[i]=boundRect[i]+Size(-45,0);		
		}
		rect_nums++;

	}*/
/*	for(int i=0;i<rect_nums;i++)
	{
		if(boundRect[i].area()<10000)
		{
			boundRect.erase(boundRect.begin()+i);
		}
	
	}*/
		
	sort(used.begin(),used.end(),cmp);
	Mat digital[4];
	for(int i=0;i<rect_num;i++)
	{

	digital[i]=bin_image(used[i]);
	}

/*
	for(int i=0;i<4;i++)
	{
		boundRect[i] = boundRect[i]+Point(2,top);//偏移量
		rectangle(src_image,boundRect[i],Scalar(0,255,0),5,0);
	}
*/

	/*******************************************************************/
        
	/**********************对单个数字进行识别并输出结果***********************/

	int k;
	for(int i=0;i<4;i++)
	{
		k=tell_num(digital[i]);
		cout<<k<<" ";
	}
	cout<<endl;
	

	/*************************************************************************/
	//dilate(dst_image,out_image,element);
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
