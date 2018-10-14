/*************************************************************
 * @file	main.cpp
 * @brief	This is the main part of the project
 * Details.
 *
 * @version	1.0.1
 * @author	Lomgahong
 * @email	1073097404@qq.com
 *
 * ------------------------------------------------------------
 *  Change History:
 *  <Date>	|<Version>	|<Author>	|<Description>
 *  -----------------------------------------------------------
 *  2018/10/14	|1.0.1		|Lomgahong	|Create file
 *
 *  ***********************************************************/

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"fun.hpp"

using namespace std;
using namespace cv;

/**
 * 主函数：
 */
int main(int argc,char** argv)
{
	//创建一些窗口（测试用）
	namedWindow("origin",CV_WINDOW_AUTOSIZE);
	namedWindow("gaussian",CV_WINDOW_AUTOSIZE);
	namedWindow("black&white",CV_WINDOW_AUTOSIZE);
	namedWindow("mark",CV_WINDOW_AUTOSIZE);
	//读入图片
	Mat img=imread(argv[1],-1);
	vector<Mat> rgb;
	Mat img_r,img_g,img_b,IMG;
	int w,h,i;
	//img:初始图像
	//IMG：只保留红色的图像
	//IMAGE：黑白图像
	//contoursIMAGE:画出轮廓的黑白图像
	if(!img.empty())
	{
		//有图片输入时才执行操作
		imshow("origin",img);
		//定义高斯滤波的参数
		GaussianBlur(img,img,Size(3,3),0,0);
		imshow("gaussian",img);
		//将图片分成三个通道
		split(img,rgb);
		//清除掉G和B通道的数值，增强R通道
		threshold(rgb[0],rgb[0],0,0,CV_THRESH_BINARY);
		threshold(rgb[1],rgb[1],0,0,CV_THRESH_BINARY);
		threshold(rgb[2],rgb[2],225,255,CV_THRESH_BINARY);
		//图像三个通道重新合并
		merge(rgb,IMG);
		//转换成灰度图象
		cvtColor(IMG,IMG,CV_RGB2GRAY);
		//新定义一个用于储存新图象的用器
		Mat IMAGE=Mat::zeros(IMG.size(),IMG.type());
		int width=IMG.cols;
		int height=IMG.rows;
		float beta=255;
		for(w=0;w<width;w++)
		{
			for(h=0;h<height;h++)
			{
				//根据灰度来改变颜色参数,使图片二值化
				float gray=IMG.at<uchar>(h,w);
				if(gray<15)
					IMAGE.at<uchar>(h,w)=saturate_cast<uchar>(beta);
				IMAGE.at<uchar>(h,w)=255-IMAGE.at<uchar>(h,w);
			}
		}
		//经过多次测试，发现本方法不适用腐蚀函数
		//Mat element=getStructuringElement(MORPH_RECT,Size,5));
		//erode(IMAGE,IMAGE,element);
		//膨胀
		Mat element=getStructuringElement(MORPH_RECT,Size(15,15));
		dilate(IMAGE,IMAGE,element);
		imshow("black&white",IMAGE);
		//寻找轮廓，先声明一些变量
		vector<vector<Point>> contours_out;
		vector<Vec4i> hierarchy;
		//应用findcontours函数
		findContours(IMAGE,contours_out,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
		const size_t size=contours_out.size();
		vector<Rect> num_location;
		for(int i=0;i<contours_out.size();i++)
		{
			//获取包住每个数字的最小矩形
			num_location.push_back(boundingRect(contours_out[i]));
		}
		//排序，过滤剩下四个最大的矩形，排除干扰
		sort(num_location.begin(),num_location.end(),cmp);
		for(i=0;i<4;i++)
		{
			//在图上画出矩形
			rectangle(IMAGE,num_location[i],Scalar(255,0,0),4.0,0.0);
		}
		imshow("mark",IMAGE);
		//穿线法：将数字区域分割成六个部分，扫描各个部分的像素点，判断该	
		//区域是否存在笔画，再根据二进制规则判断出数字的值		
		int result[4];
		for(i=0;i<4;i++)
			//调用getnumber函数
			result[i]=getnumber(num_location[i],IMAGE);
		transform(result);
		//输出结果
		cout<<"识别到的数字为：";
		for(i=0;i<4;i++)
			cout<<result[i];
		cout<<endl;
	}
		else		
		cout<<"ERROR"<<endl;
	waitKey(0);
	//释放窗口
	destroyAllWindows();
	return 0;
}
