/***************************************** 
*tube.cpp                    
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/14 
*
*Abustract: 实现头文件函数
****************************************/ 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../inc/tube.hpp"

using namespace std;
using namespace cv;

int movehighlight(IplImage* src,IplImage* dst )
{
	int height=src->height;
    int width=src->width;
    int step=src->widthStep;
    int i=0,j=0;
         unsigned char R,G,B,MaxC;
         double alpha,beta,alpha_r,alpha_g,alpha_b,beta_r,beta_g,beta_b,temp=0,realbeta=0,minalpha=0;
         double gama,gama_r,gama_g,gama_b;
         unsigned char* srcData;
         unsigned char* dstData;
        for (i=0;i<height;i++)
         {
              srcData=(unsigned char*)src->imageData+i*step;
              dstData=(unsigned char*)dst->imageData+i*step;
              for (j=0;j<width;j++)
               {
                     R=srcData[j*3];
                    G=srcData[j*3+1];
                    B=srcData[j*3+2];
   
                  alpha_r=(double)R/(double)(R+G+B);
                 alpha_g=(double)G/(double)(R+G+B);
                 alpha_b=(double)B/(double)(R+G+B);
                 alpha=max(max(alpha_r,alpha_g),alpha_b);
                 MaxC=max(max(R,G),B);
                 // compute the maximum of the rgb channels
                 minalpha=min(min(alpha_r,alpha_g),alpha_b);                 
                 beta_r=1-(alpha-alpha_r)/(3*alpha-1);
                 beta_g=1-(alpha-alpha_g)/(3*alpha-1);
                 beta_b=1-(alpha-alpha_b)/(3*alpha-1);
                 beta=max(max(beta_r,beta_g),beta_b);
                 //将beta当做漫反射系数，则有                 
                 // gama is used to approximiate the beta
                 gama_r=(alpha_r-minalpha)/(1-3*minalpha);
                 gama_g=(alpha_g-minalpha)/(1-3*minalpha);
                 gama_b=(alpha_b-minalpha)/(1-3*minalpha);
                 gama=max(max(gama_r,gama_g),gama_b);   
     
                 temp=(gama*(R+G+B)-MaxC)/(3*gama-1);
                 //beta=(alpha-minalpha)/(1-3*minalpha)+0.08;
                 //temp=(gama*(R+G+B)-MaxC)/(3*gama-1);
                dstData[j*3]=R-(unsigned char)(temp+0.5);
                dstData[j*3+1]=G-(unsigned char)(temp+0.5);
                dstData[j*3+2]=B-(unsigned char)(temp+0.5);   
        }
    } 
    return 1;
}
