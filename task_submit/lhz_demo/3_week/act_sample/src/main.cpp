/***************************************** 
*main.cpp                     
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/14 
*
*Abustract: The main program
****************************************/ 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "../inc/tube2.hpp"

using namespace std;
using namespace cv;

void detect(IplImage * img, char * strnum, CvRect rc);
int list[10][2] = {0};  //1列坐标，2列字符数值
int l = 0;  //字符个数

int main()
{
	IplImage * src_img= cvLoadImage("act_sample7.jpg");
    if(!src_img)
    {
        printf("src_img could not be load\n");
        return -1;
    }
    cvShowImage("原图像",src_img);

    Mat roiImage,srcImage;
    srcImage = imread("act_sample7.jpg");
    srcImage(Rect(220, 220, 400, 160)).copyTo(roiImage);


    IplImage imgTmp = roiImage;
    src_img = cvCloneImage(&imgTmp);


    IplImage* src = src_img;
    //movehighlight(src,src_img);

    int width = src_img->width;
    int height = src_img->height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            CvScalar s_src_img = cvGet2D(src_img, i, j);//获取像素点为（j, i）点的HSV的值 
            CvScalar s;
            if (!(((s_src_img.val[0]>0)&&(s_src_img.val[0]<45)) || (s_src_img.val[0]>120)&&(s_src_img.val[0]<180)))
            {
                s.val[0] =0;
                s.val[1]=0;
                s.val[2]=0;
                cvSet2D(src_img, i ,j, s);
            }
        }
    }
        movehighlight(src_img,src_img);
    cvShowImage("去除反光效果", src_img);  //src img

    IplImage * gray_img = cvCreateImage(cvGetSize(src_img), src_img->depth, 1);
    cvCvtColor(src_img, gray_img, CV_BGR2GRAY);

    IplImage * adp_img = cvCreateImage(cvGetSize(src_img), src_img->depth, 1);
    int threshold_type = CV_THRESH_BINARY_INV;  
    int adaptive_method = CV_ADAPTIVE_THRESH_GAUSSIAN_C;  //CV_ADAPTIVE_THRESH_MEAN_C  
    int block_size = 7;  
    double offset = 5; 

    //cvAdaptiveThreshold(gray_img, adp_img, 255, adaptive_method, threshold_type, block_size, offset);
    cvThreshold(gray_img, adp_img, 32, 255, CV_THRESH_BINARY); 
    //二值化图片

    IplImage * xtx_img = cvCreateImage(cvGetSize(adp_img), adp_img->depth, adp_img->nChannels);
    cvCopy(adp_img, xtx_img);
    IplConvKernel * kernal; 
    //自定义 1x3 的核进行 x 方向的膨胀腐蚀
    kernal = cvCreateStructuringElementEx(1, 3, 0, 1, CV_SHAPE_RECT);
    cvDilate(xtx_img, xtx_img, kernal,12);
    cvErode(xtx_img, xtx_img, kernal, 10);   //y 腐蚀去除碎片      
    //自定义 3x1 的核进行 y 方向的膨胀腐蚀
    kernal = cvCreateStructuringElementEx(3, 1, 1, 0, CV_SHAPE_RECT);
    cvDilate(xtx_img, xtx_img, kernal, 12);   //x 膨胀回复形态
    cvErode(xtx_img, xtx_img, kernal, 10);    //x 腐蚀去除碎片 
    
    IplImage * temp_img = cvCreateImage(cvGetSize(xtx_img), xtx_img->depth, adp_img->nChannels);
    cvCopy(xtx_img, temp_img);
    cvShowImage("腐蚀膨胀之后", temp_img);


    CvSeq * contours = NULL;
    CvMemStorage * storage = cvCreateMemStorage(0);
    int count = cvFindContours(xtx_img, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
    printf("The count is :%d\n", count);
    int idx = 0;
    char szName[56] = {0};
    int tempcount = 0;
    CvSeq * c=contours;
    for( ; c!=NULL; c=c->h_next)
    {
        CvRect rc = cvBoundingRect(c, 0);
        double tmparea = fabs(cvContourArea(c));  
        if(tmparea > ((src_img->height*src_img->width)/4))     
        {    
            cvSeqRemove(c,0); //删除面积大于设定值的轮廓,1/4    
            continue;    
        }  
        if(tmparea < ((src_img->height*src_img->width)/100))     
        {    
            cvSeqRemove(c,0); //删除面积小于设定值的轮廓,1/20   
            continue;    
        }

        //cvDrawRect(src_img, cvPoint(rc.x, rc.y), cvPoint(rc.x+rc.width, rc.y+rc.height), CV_RGB(255, 0, 0));
        IplImage * sub_img = cvCreateImage(cvSize(rc.width, rc.height), xtx_img->depth, adp_img->nChannels);
        cvSetImageROI(temp_img, rc);
        cvCopy(temp_img, sub_img);
        cvResetImageROI(temp_img);      
        sprintf(szName, "win_%d", idx++);
        detect(sub_img, szName, rc);    //DETECT NUMBER
        cvShowImage(szName, sub_img);
        //cvReleaseImage(&sub_img);
    }
    printf("\n字符识别结果为：");
    for(int i=0; i<l; i++)
    {
        for(int j=0; i+j<l-1; j++)
        {
            if(list[j][0] > list[j + 1][0])
            {
                //坐标排序
                int temp = list[j][0];
                list[j][0] = list[j + 1][0];
                list[j + 1][0] = temp;
                //数值随之变化
                temp = list[j][1];
                list[j][1] = list[j+1][1];
                list[j+1][1] = temp;
            }
        }
    }
    for(int i=0; i<l; i++)
    {
        
        printf("%d ", list[i][1]);
    }
    printf("\n");
    cvShowImage("src", src_img);    //src img
    cvWaitKey(0);
    return 1;
}


void detect(IplImage * img, char * strnum, CvRect rc)
{
    printf("\n模块 %s\n", strnum);

    //printf("高度 %d\n", img->height);
    //printf("宽度 %d\n", img->width);

    list[l][0] = rc.x;  //第l个字符横坐标

    //if the height is more two longer than width,number is 1
    if((img->height/img->width)>2)
    {
        list[l][1] = 1;
        printf("字符是 1.\n");
    }

    else 
    {
        int ld[3] = {0};
        CvScalar pix;       

        int i = img->width/2;
        int j = img->height/3;
        int k = img->height*2/3;

        //竖向扫描
        for(int m=0; m<3; m++)
        {
            for(int n=m*j; n<(m+1)*j; n++)
            {
                pix = cvGet2D(img, n, i);
                if(pix.val[0]==255)
                {
                    ld[0]++;
                    break;
                }
            }
        }
        printf("竖向 %d\n", ld[0]);

        //横向扫描
        for(int m=0; m<2; m++)
        {
            for(int n=m*i; n<(m+1)*i; n++)
            {
                //横向1/3扫描
                pix = cvGet2D(img, j, n);
                if(pix.val[0]==255)
                {
                    ld[1]++;
                    break;
                }
            }
        }
        printf("横向1 %d\n", ld[1]);

        //横向扫描
        for(int m=0; m<2; m++)
        {
            for(int n=m*i; n<(m+1)*i; n++)
            {
                //横向2/3扫描
                pix = cvGet2D(img, k, n);
                if(pix.val[0]==255)
                {
                    ld[2]++;
                    break;
                }
            }
        }
        printf("横向2 %d\n", ld[2]);

        if((ld[0]==2)&&(ld[1]==2)&&(ld[2]==2))
        {
            printf("字符是 0\n");
            list[l][1] = 0;
        }
        else if((ld[0]==1)&&(ld[1]==2)&&(ld[2]==1))
        {
            printf("字符是 4\n");
            list[l][1] = 4;
        }
        else if((ld[0]==3)&&(ld[1]==1)&&(ld[2]==2))
        {
            printf("字符是 6\n");
            list[l][1] = 6;
        }
        else if((ld[0]==1)&&(ld[1]==1)&&(ld[2]==1))
        {
            printf("字符是 7\n");
            list[l][1] = 7;
        }
        else if((ld[0]==3)&&(ld[1]==2)&&(ld[2]==2))
        {
            printf("字符是 8\n");
            list[l][1] = 8;
        }
        else if((ld[0]==3)&&(ld[1]==2)&&(ld[2]==1))
        {
            printf("字符是 9\n");
            list[l][1] = 9;
        }
        else if((ld[0]==3)&&(ld[1]==1)&&(ld[2]==1))
        {
            int l1=0, l2=0;         
            //横向扫描
            int k = img->height/3;
            for(int i=0; i<img->width/2; i++)
            {
                //横向2/3扫描
                pix = cvGet2D(img, k, i);
                if(pix.val[0]==255)
                {
                    l1++;
                    break;
                }
            }
            //横向扫描
            k = img->height*2/3;
            for(int i=0; i<img->width/2; i++)
            {
                //横向2/3扫描
                pix = cvGet2D(img, k, i);
                if(pix.val[0]==255)
                {
                    l2++;
                    break;
                }
            }
            if((l1==0)&&(l2==0))
            {
                printf("字符是 3\n");
                list[l][1] = 3;
            }
            else if((l1==0)&&(l2==1))
            {
                printf("字符是 2\n");
                list[l][1] = 2;
            }
            else if((l1==1)&&(l2==0))
            {
                printf("字符是 5\n");
                list[l][1] = 5;
            }
        }
        else printf("识别失败\n");
    }
    l++;
}

