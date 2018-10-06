#include<ratio>
#include<iomanip>
#include<unistd.h>
#include<string>
#include"Timer.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

using namespace std::chrono; 


//�򿪴��ڡ�������ʾһ����ӭͼƬ
int Timer::open()
{
	
	image=imread("th.jpg",1) ;//???
	if (image.data == nullptr) //���ݲ�����,�������ļ�������
    	{
        	cerr << "�ļ�������." << endl;//cerr??? 
        	return 0;
    	}
    else
    {
    	namedWindow("counter");
    	imshow("counter",image);
    	waitKey(0);//���߳� 
	return 0;
	}
}

//��ʼ��ʱ�����ڳ������Ӽ�ʱ��ʾ���ն�Ҳͬʱ���������
//ͼƬ���ڼ�����������С����һλ���ն˼�ʱ����ÿ�����һ��
void Timer::startTiming()
{
	//����ʱ���� 
    //std::chrono::steady_clock �����Ҫ��ǰ����� using namespace std::chrono;
    steady_clock::time_point t1 = steady_clock::now();//��¼��ʼʱ��  
	//for(int i=1;i<10;i++)
	{
		IplImage* pImg = cvLoadImage("th.jpg",1); 
		
		usleep(100000);//��λΪms//��ͣ0.1s�������̣߳��� 
		imshow("counter",image);
    	steady_clock::time_point t2 = steady_clock::now();//��¼�ڶ���ʱ��
    	cout<<2<<endl;
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);//����ʱ����
		
		CvFont font;  
    	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0f, 1.0f, 0, 5, 8);
    	cvPutText(pImg, "to_string(floor(time_span.count()*10)/10).c_str() s", cvPoint(200, 200), &font, CV_RGB(255,0,0));

		//cvPutText(pImg,to_string(floor(time_span.count()*10)/10).c_str(),cvPoint(50,60),CV_FONT_HERSHEY_SIMPLEX,cv::Scalar(255,23,0));//��ͼƬ��д����
		//pImg, "This is a picture named lena!", cvPoint(50, 50), &font, CV_RGB(255,0,0)
		int i;
		cin>>i;
		
	
	}
	//std::cout << "It took me " << time_span.count() << " seconds."<<endl;//���ʱ���� 
}

void Timer::stopTiming()//������ʱ�����ڻָ���ӭͼƬ��
{
	imshow("counter",image);
}

void Timer::close()//�رմ��ڡ�
{
	
} 

void Timer::pause()//��ͣ��ʱ�����ڱ��ֲ���
{
	//wait();
}

void Timer::resume()//��ԭ������������ʱ
{
	//notify();
}
