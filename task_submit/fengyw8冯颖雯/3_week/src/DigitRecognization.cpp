#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include<algorithm>
#include<string>
#include"utility.h"
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img = imread(argv[1],1);
    imshow("原图",img);//显示原图
    Mat dstImage1,dstImage2;
    
    
    //step1.预处理
    //1.1遍历图像，利用RGB二值化(R值+亮度+饱和度)
	for (int i = 0; i<img.rows; i++)
	{
		for (int j = 0; j<img.cols; j++)
		{
		    auto r=img.at<Vec3b>(i, j)[2];
		    auto g=img.at<Vec3b>(i, j)[1];
		    auto b=img.at<Vec3b>(i, j)[0];
			if(r>180 && 0.3*r+0.6*g+0.1*b<200 && 0.5*r-0.4187*g-0.08136*b+128>120) //(R值+亮度+饱和度)
			{
			    img.at<Vec3b>(i, j)[2]=img.at<Vec3b>(i, j)[1]=img.at<Vec3b>(i, j)[0]=255;
			}
			else
			    img.at<Vec3b>(i, j)[2]=img.at<Vec3b>(i, j)[1]=img.at<Vec3b>(i, j)[0]=0;
		}
	}
	
	//1.2利用腐蚀及膨胀处理图像，实现滤波
    Mat element1 = getStructuringElement( 0,Size(2, 2) , Point(-1, -1 ));
    Mat element2 = getStructuringElement( 0,Size(20, 20) , Point(-1, -1 ));
    erode(img,dstImage1,element1);//腐蚀
    imshow("腐蚀", dstImage1);//显示腐蚀图像
    dstImage1=dstImage1(Range(10,dstImage1.rows),Range(0,dstImage1.cols));//对图像切割处理
    if(isact(dstImage1))//判断是否是act_sample，调用isact函数
        dstImage1=dstImage1(Range(dstImage1.rows*1/3,dstImage1.rows*2/3),Range(dstImage1.cols*7/24,dstImage1.cols*17/24));//切割图像
    dilate(dstImage1,dstImage2,element2);//膨胀      
    imshow("膨胀", dstImage2);
    //imshow("截图", dstImage2);


    //step2.分割
    //2.1canny寻找轮廓
    Mat result;
    Canny(dstImage2, result, 50, 150); 
    vector<vector<Point> > contours;  
    vector<Vec4i> hierarchy;  
    findContours(result, contours, hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE); 
    
    //2.2画出轮廓并分割
    Mat img1;  
    Mat img2;  
    Mat img3;  
    Mat img4;  
    psort(contours);
    //2.2.1分割
    for(int i=0;i<contours.size();i++)  
    {  
        Rect rect = boundingRect(Mat(contours[i]));  
        Mat roi = dstImage2(rect); 
        roi.convertTo(img1, roi.type());
        string s="img"+to_string(i+1);
        int tube=TubeIdentification(img1);
        if(tube>=0)
            cout<<tube;
    } 
    cout<<endl;
    //2.2.2画出轮廓（定位数字）
    for(int i=0; i<contours.size();i++)
    {
        Rect rect = boundingRect(Mat(contours[i]));  
        rectangle(dstImage2, rect.tl(), rect.br(),Scalar(0,255,0),2);  
    }
    imshow("定位数字", dstImage2);
   
      
    waitKey(0);
    
    return 0;
}


