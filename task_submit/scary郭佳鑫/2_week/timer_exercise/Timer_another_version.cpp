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
double time=0;
cin>>str;
//主循环
while(key){
        if(str=="quit")key=false;
        else if(str=="start"){
                cout<<(int)time<<endl;
                sprintf(num_to_str,"%d",(int)time);
                //刷新背景
                image.setTo(cv::Scalar(100, 0, 0));
                //在图片上写文字
                 putText(image,num_to_str,Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
		//显示绘制结果
                cv::imshow("welcome!", image);

                waitKey(1000);
		time++;
        }
        else if(str=="stop"){
                //刷新背景
                image.setTo(cv::Scalar(100, 0, 0));
                putText(image,"0",Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
                //显示绘制结果
                cv::imshow("welcome!", image);
                time=0;
        }
        else if(str=="pause"){
		//doing nothing
        }

        else if(str=="resume"){
		time++;
                sprintf(num_to_str,"%d",(int)time);
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
                          
