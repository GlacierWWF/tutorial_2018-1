/*********************************************************
 * Digit_Tube image Recognition by opencv
 *
 * @author	Floyed_Shen
 * @email	Floyed_Shen@outlook.com
 * @version	1.0.0
 * @date	2018/10/12
 *********************************************************/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect/objdetect_c.h>
#include "./inc/Digit_Tube.h"
int main(){
    int model;
    std::string pwd="./input/",filename1,filename2,s1,s2,type=".jpg";
    while(std::cin>>model){
        Digit_Tube dt;
        if(!model){
            std::cin>>filename1;
            s1=pwd+filename1+type;
            dt=Digit_Tube(s1.c_str());
        }else if(model==1){
            std::cin>>filename1>>filename2;
            s1=pwd+filename1+type;
            s2=pwd+filename2+type;
            dt=Digit_Tube(s1.c_str(),s2.c_str());
        }
        if(!dt.open()){
            puts("fail to open the imagine!");
            continue;
        }
        dt.identify();
        dt.print();
        cv::waitKey(1);
    }
    return 0;
}