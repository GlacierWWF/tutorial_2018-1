#ifndef UTILITY
#define UTILITY
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include<algorithm>
#include<string>
using namespace cv;
using namespace std;

bool isact(Mat img)//判断是否为act_simple
{
    for(int row=0;row<=10;row++)
        for(int col=0;col<img.cols;col++)
            if(img.at<Vec3b>(row, col)[2]>200)
                return true;
    return false;
}

void swap(vector<vector<Point>>& contours,int a,int b)
{
    vector<Point> temp;
    temp=contours[a];
    contours[a]=contours[b];
    contours[b]=temp;
    return;
}

void psort(vector<vector<Point>>& contours)//排序（按照坐标从左到右）
{
    for(int i=1;i<contours.size();i++)
    {
        for(int j=0;j<contours.size()-i;j++)
            if(contours[j][0].x>contours[j+1][0].x)
                swap(contours,j,j+1);
    }
}

bool Iswhite(Mat inputmat,int row,int col)//判断是否为白色
{
    return inputmat.at<Vec3b>(row, col)[2]>200;
}


//数字识别（穿线法）
int TubeIdentification(Mat inputmat) // 穿线法判断数码管a、b、c、d、e、f、g
{
	if(inputmat.rows>inputmat.cols*2.5)
	    return 1;
    int tube = 0;
    int tubo_roi[7][2] =
    {
        { 10,inputmat.cols/2}, // a
        { inputmat.rows * 1 / 4,inputmat.cols-10}, // b
        { inputmat.rows * 3 / 4,inputmat.cols-10}, // c
        { inputmat.rows-10,inputmat.cols * 1 / 2,}, // d
        { inputmat.rows * 3 / 4,10}, // e
        { inputmat.rows * 1 / 4,10}, // f
        { inputmat.rows * 1 / 2,inputmat.cols * 1 / 2}, // g
    };

    if (inputmat.rows / inputmat.cols > 2)  
    {
        tube = 6;
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {

            if (Iswhite(inputmat, tubo_roi[i][0] , tubo_roi[i][1]))
                tube = tube + (int)pow(2, i);
        }
    }

    switch (tube)
    {
        case  63: return 0;  break;
        case   6: return 1;  break;
        case  91: return 2;  break;
        case  79: return 3;  break;
        case 102: return 4;  break;
        case 109: return 5;  break;
        case 125: return 6;  break;
        case   7: return 7;  break;
        case 127: return 8;  break;
        case 111: return 9;  break;

        default: return -1;
    }
}

#endif
