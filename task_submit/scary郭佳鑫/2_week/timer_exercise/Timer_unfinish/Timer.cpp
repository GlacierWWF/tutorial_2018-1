Timer(){};
~Timer(){};
void Timer::open(){
//创建空白图用于绘制文字
cv::Mat image = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
//设置蓝色背景
image.setTo(cv::Scalar(100, 0, 0));
//窗口命名
namedWindow("welcome!");
//显示绘制结果
cv::imshow("welcome!", image);
//显示提示语
cout<<"Enter 'start' to start counting..."<<endl;
cout<<"Enter 'stop' to stop counting..."<<endl;
cout<<"Enter 'pause' to pause..."<<endl;
cout<<"Enter 'resume' to continue..."<<endl;
cout<<"Enter 'quit' to close the window..."<<endl;

}

void Timer::close(){
key=false;
destroyAllWindows();
}
void Timer::startTiming(){
static chrono::steady_clock::time_point t0=chrono::steady_clock::now();
chrono::steady_clock::time_point t1=chrono::steady_clock::now();
chrono::duration<double>time_used=chrono::duration_cast<chrono::duration<double>>(t1-t0);
cout<<(int)time_used.count()<<endl;
char num_to_str[10];
sprintf(num_to_str,"%d",(int)time_used.count());
}

void Timer::stopTiming(){

};

void Timer::resume(){
//刷新背景
image.setTo(cv::Scalar(100, 0, 0));
//在图片上写文字
putText(image,num_to_str,Point(50,100),FONT_HERSHEY_SIMPLEX,1,Scalar(255,23,0),4,8);
//显示绘制结果
cv::imshow("welcome!", image);
};

void Timer::pause(){

};

                        
