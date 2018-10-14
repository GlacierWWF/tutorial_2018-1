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
    imshow("ԭͼ",img);//��ʾԭͼ
    Mat dstImage1,dstImage2;
    
    
    //step1.Ԥ����
    //1.1����ͼ������RGB��ֵ��(Rֵ+����+���Ͷ�)
	for (int i = 0; i<img.rows; i++)
	{
		for (int j = 0; j<img.cols; j++)
		{
		    auto r=img.at<Vec3b>(i, j)[2];
		    auto g=img.at<Vec3b>(i, j)[1];
		    auto b=img.at<Vec3b>(i, j)[0];
			if(r>180 && 0.3*r+0.6*g+0.1*b<200 && 0.5*r-0.4187*g-0.08136*b+128>120) //(Rֵ+����+���Ͷ�)
			{
			    img.at<Vec3b>(i, j)[2]=img.at<Vec3b>(i, j)[1]=img.at<Vec3b>(i, j)[0]=255;
			}
			else
			    img.at<Vec3b>(i, j)[2]=img.at<Vec3b>(i, j)[1]=img.at<Vec3b>(i, j)[0]=0;
		}
	}
	
	//1.2���ø�ʴ�����ʹ���ͼ��ʵ���˲�
    Mat element1 = getStructuringElement( 0,Size(2, 2) , Point(-1, -1 ));
    Mat element2 = getStructuringElement( 0,Size(20, 20) , Point(-1, -1 ));
    erode(img,dstImage1,element1);//��ʴ
    imshow("��ʴ", dstImage1);//��ʾ��ʴͼ��
    dstImage1=dstImage1(Range(10,dstImage1.rows),Range(0,dstImage1.cols));//��ͼ���и��
    if(isact(dstImage1))//�ж��Ƿ���act_sample������isact����
        dstImage1=dstImage1(Range(dstImage1.rows*1/3,dstImage1.rows*2/3),Range(dstImage1.cols*7/24,dstImage1.cols*17/24));//�и�ͼ��
    dilate(dstImage1,dstImage2,element2);//����      
    imshow("����", dstImage2);
    //imshow("��ͼ", dstImage2);


    //step2.�ָ�
    //2.1cannyѰ������
    Mat result;
    Canny(dstImage2, result, 50, 150); 
    vector<vector<Point> > contours;  
    vector<Vec4i> hierarchy;  
    findContours(result, contours, hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE); 
    
    //2.2�����������ָ�
    Mat img1;  
    Mat img2;  
    Mat img3;  
    Mat img4;  
    psort(contours);
    //2.2.1�ָ�
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
    //2.2.2������������λ���֣�
    for(int i=0; i<contours.size();i++)
    {
        Rect rect = boundingRect(Mat(contours[i]));  
        rectangle(dstImage2, rect.tl(), rect.br(),Scalar(0,255,0),2);  
    }
    imshow("��λ����", dstImage2);
   
      
    waitKey(0);
    
    return 0;
}


