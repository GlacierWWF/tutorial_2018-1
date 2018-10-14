#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <stdio.h>  
#include <iostream>  
using namespace cv;  
using namespace std;   
  
  
void getPXSum(Mat &src, int &a)//获取所有像素点和  
{   
    threshold(src, src, 100, 255, CV_THRESH_BINARY);  
      a = 0;  
    for (int i = 0; i < src.rows;i++)  
    {  
        for (int j = 0; j < src.cols; j++)  
        {  
            a += src.at <uchar>(i, j);  
        }  
    }  
}  
//像素匹配算法还没有完成  
/* 
int  getSubtract(Mat &src, int TemplateNum) //两张图片相减 
{ 
    Mat img_result; 
    int min = 1000000; 
    int serieNum = 0; 
    for (int i = 0; i < TemplateNum; i++){ 
        char name[20]; 
        sprintf_s(name, "D:\\%dLeft.jpg", i); 
        Mat Template = imread(name, CV_LOAD_IMAGE_GRAYSCALE); 
        threshold(Template, Template, 100, 255, CV_THRESH_BINARY); 
        threshold(src, src, 100, 255, CV_THRESH_BINARY); 
        resize(src, src, Size(32, 48), 0, 0, CV_INTER_LINEAR); 
        resize(Template, Template, Size(32, 48), 0, 0, CV_INTER_LINEAR);//调整尺寸       
        //imshow(name, Template); 
        absdiff(Template, src, img_result);// 
        getPXSum(img_result, diff); 
        if (diff < min) 
        { 
            min = diff; 
            serieNum = i; 
        } 
    } 
    cout<<serieNum<<serieNum<<endl; 
    return serieNum; 
}*/  
   
bool cmp(const Rect& a, const Rect& b)  
{  
    if (a.x < b.x)  
        return true;  
    else  
        return false;  
}  
  
  
int getColSum(Mat& bimg, int col)  
  {  
     int height = bimg.rows;  
      int sum = 0;  
      for (int i = 1; i < height; i++)  
      {  
          sum += bimg.at<uchar>(i, col);  
      }  
      cout << sum << endl;  
     return sum;  
 }  
  
int main()  
{  
  
  Mat image_org = imread("sim_sample1.jpg", IMREAD_COLOR);  
  imshow("sim_sample1.jpg", image_org);  // read RGB image  
  Mat image_gry = imread("sim_sample1.jpg", IMREAD_GRAYSCALE);  
  if (image_gry.empty()) // read RGB image  
    return -1;  
//imshow("image_gry", image_gry);  
  
  Mat image_bin;  
  threshold(image_gry, image_bin, 50, 255, THRESH_BINARY); // convert to binary image  
  imshow("image_bin", image_bin);  
  
  Mat image_dil;  
  Mat element = getStructuringElement(MORPH_RECT, Size(10, 10)); // 膨胀  
  dilate(image_bin, image_dil, element);  
  imshow("image_dil", image_dil);  
  
  
  int height=image_dil.rows;  
  int width=image_dil.cols;   
  Mat piece=image_dil;  
  Rect m_select = Rect(0,0,width/4,height);  
  Rect m_select2 = Rect(width/4,0,width/4,height);  
  Rect m_select3 = Rect(width/2,0,width/4,height);  
  Rect m_select4 = Rect(3*width/4,0,width/4,height);  
  
   
    Mat ROI = piece(m_select);  
        Mat ROI2 = piece(m_select2);  
        Mat ROI3 = piece(m_select3);  
        Mat ROI4 = piece(m_select4);  
   
    imshow("剪裁图", ROI);  
    imshow("剪裁图2", ROI2);  
        imshow("剪裁图3", ROI3);  
        imshow("剪裁图4", ROI4);  
  
  
  
  
waitKey(0);  
    return 0;  
  
}  
