/*********************************************************
 * Timer
 *
 * @author	Floyed_Shen
 * @email	Floyed_Shen@outlook.com
 * @version	1.0.0.0
 * @date	2018/10/4
 */
#include "../inc/timer.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include <cstdio>
#include <iostream>
#include<ctime>
#include<cstring>
using namespace std;
using namespace cv;
using namespace chrono;
Timer::Timer(){
    action=0;
    tmp=0;
    second_now=0;
    mat=imread("pic/test.jpg");
    org.x=(int)mat.rows*2/5;
    org.y=(int)mat.cols*4/5;
    putText(mat,author_name,org,1,2,Scalar(0,255,255),5,8);
    org.x=(int)mat.rows/5;
    org.y=(int)mat.cols/5;
    strcpy(tim_str,"Welcome");
}
Timer::~Timer(){

}
void Timer::int2str(int x){
    if(x/1000==second_now){
        //cout<<x<<endl;
        printf("time: %d\n",second_now);
        second_now++;
    }
    int cnt=0;
    while(x){
        tim_str[cnt]=x%10+'0';
        cnt++;
        x=x/10;
        //cout<<x<<endl;
    }
    while(cnt<5){
        tim_str[cnt]='0';
        cnt++;
    }
    for(int i=0;i<cnt/2;i++){
        swap(tim_str[i],tim_str[cnt-1-i]);
    }
    for(int i=cnt-1;i>=cnt-3;i--){
        tim_str[i+1]=tim_str[i];
    }
    tim_str[cnt+1]='s';
    tim_str[cnt-3]='.';
    return;
}
void Timer::write(const int& tim){
    //mat=imread("picture1.jpg");
    Mat b=mat.clone();
    putText(b,tim_str,org,1,4,Scalar(0,0,0),5,8);
    imshow(window_name,b);
    waitKey(tim);
}
void scan(int &action){
    char cmd[10];
    while(1){
        scanf("%s",cmd);
        printf("[INFO]");
        if(!strcmp(cmd,"start")&&(action==2||action==0)){
            action=1;
        }else if(!strcmp(cmd,"end")&&action!=2){
            action=2;
        }else if(!strcmp(cmd,"pause")&&action==1){
            action=3;
        }else if(!strcmp(cmd,"resume")&&action==3){
            action=4;
        }else{
            strcpy(cmd,"cmd wrong!");
        }puts(cmd);
    }
}
void Timer::startTiming(){
    write(1);
}
void Timer::stopTiming(){
    write(1);
}
void Timer::pause(){
    write(1);
}
void Timer::resume(){
    action=1;
}
void Timer::open(){
    namedWindow(window_name,CV_WINDOW_AUTOSIZE);
    input=thread(scan,ref(action));
    run();
}
void Timer::run(){
    bool flag=0;
    auto start_chrono=steady_clock::now();
    auto end_chrono=steady_clock::now();
    auto duration=duration_cast<microseconds>(end_chrono-start_chrono);
    auto now_chrono=steady_clock::now();
    auto pause_duration=duration_cast<microseconds>(now_chrono-end_chrono);
    while(1){
        if(action==0){
            write(1);
        }else if(action==1){
            if(!flag){
                flag=1;
                memset(tim_str,0,sizeof tim_str);
                start_chrono=steady_clock::now();
            }
            end_chrono=steady_clock::now();
            duration=duration_cast<microseconds>(end_chrono-start_chrono);
            dur=int(duration.count())/1000;
            int2str(dur-tmp);
            startTiming();
        }else if(action==2){
            flag=0;
            dur=0;
            tmp=0;
            second_now=0;
            strcpy(tim_str,"END!");
            stopTiming();
        }else if(action==3){
            pause();
        }else if(action==4){
            now_chrono=steady_clock::now();
            pause_duration=duration_cast<microseconds>(now_chrono-end_chrono);
            tmp+=int(pause_duration.count())/1000;
            resume();
        }
    }
}
