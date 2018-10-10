#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<chrono>
#include<atomic>
#include<thread>
#include<mutex>
#include<opencv2/opencv.hpp>
#include<string>
#include<unistd.h>
using namespace cv;
using namespace std;
string str;
void* thread_func(void *arg){
getline(cin,str);
}

int main(int argc,char**argv){
//创建空白图用于绘制文字
cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
//设置蓝色背景
image.setTo(cv::Scalar(100, 0, 0));
//窗口命名
namedWindow("welcome!");
//显示绘制结果
cv::imshow("welcome!", image);
waitKey(1);
//显示提示语
cout<<"Enter 'start' to start counting..."<<endl;
cout<<"Enter 'stop' to stop counting..."<<endl;
cout<<"Enter 'pause' to pause..."<<endl;
cout<<"Enter 'resume' to continue..."<<endl;
cout<<"Enter 'quit' to close the window..."<<endl;
//循环开关
bool key=true;
char num_to_str[10];
double time;
//主循环
while(key){
	pthread_t a_thread;
	void*result;
	if(pthread_create(&a_thread,NULL,thread_func,NULL)!=0){
        	printf("fail to pthread_create");
        	exit(-1);
	}
	pthread_join(a_thread,&result);
	if(str=="quit")key=false;
	else if(str=="start"){
		static chrono::steady_clock::time_point t0=chrono::steady_clock::now();
		chrono::steady_clock::time_point t1=chrono::steady_clock::now();
		chrono::duration<double>time_used=chrono::duration_cast<chrono::duration<double>>(t1-t0);
		time=time_used.count();
		cout<<(int)time<<endl;
		
		sprintf(num_to_str,"%d",(int)time);
     		//刷新背景
      		image.setTo(cv::Scalar(100, 0, 0));
		//在图片上写文字
                 putText(image,num_to_str,Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
		//显示绘制结果
	        cv::imshow("welcome!", image);
		waitKey(1000);
	}
	else if(str=="stop"){
        	//刷新背景
        	image.setTo(cv::Scalar(100, 0, 0));
		putText(image,"0",Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
		//显示绘制结果
	        cv::imshow("welcome!", image);
		waitKey(1000);
	}
        else if(str=="pause"){
        }

	else if(str=="resume"){
        	static chrono::steady_clock::time_point t2=chrono::steady_clock::now();
        	chrono::steady_clock::time_point t3=chrono::steady_clock::now(); 
		chrono::duration<double>time_used=chrono::duration_cast<chrono::duration<double>>(t3-t2);
        	cout<<(int)(time_used.count()+time)<<endl;
        	sprintf(num_to_str,"%d",(int)(time_used.count()+time));
        	//在图片上写文字
        	putText(image,num_to_str,Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
		//显示绘制结果
        	cv::imshow("welcome!", image);
		waitKey(1000);

	}

}
destroyAllWindows();
return 0;
}
