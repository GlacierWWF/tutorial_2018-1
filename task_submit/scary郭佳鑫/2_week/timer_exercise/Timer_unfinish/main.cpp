#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<chrono>
#include<atomic>
#include<thread>
#include<mutex>
#include<opencv2/opencv.hpp>
#include<string>
using namespace cv;
using namespace std;
//循环开关
bool key=true;
//全局变量
string str;
cin>>str;
char num_to_str[10];


int main(int argc,char**argv){
open();
while(key){
        if(str=="quit")close();
        else if(str=="start"){
		startTiming();
		resume();
 		waitKey(1000);
        }
        else if(str=="stop")stop();
        else if(str=="pause")pause();
        else if(str=="resume")resume();

}

return 0;
}
