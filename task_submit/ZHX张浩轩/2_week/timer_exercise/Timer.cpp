#include"Timer.h"
#include<iostream>
#include<string>
#include<chrono>
#define debug
using namespace std;
using namespace chrono;
Timer::Timer()
{
    int_count = 0;
    point_count = 0;
    if_continue = true;
}
void Timer::open()
{
    time_img = imread("welcome.jpg");
    imshow("Welcome!", time_img);
}
void Timer::startTiming(float pass_time)
{
    time_img = imread("welcome.jpg");
    typedef duration<float, ratio<1, 10>> ourtime;//自定义时间类型
    string temp;
    string text = "0.0 s";//text取小数点前的数字和小数点后一位
    int i;
    int baseline;
    float value;//用于存储时间差
    Size text_size = getTextSize(text, FONT_HERSHEY_COMPLEX, 2, 1, &baseline);//获得文本框的大小
    Point origin;//在图片的中间部分输出, 因数字个数差异不大, 所以标记这一次位置
    origin.x = time_img.cols / 2 - text_size.width / 2;
    origin.y = time_img.rows / 2 + text_size.height / 2;
    auto start = system_clock::now();//开始时间
    auto end = system_clock::now();//利用auto自动赋予类型
    auto now_time = duration_cast<ourtime>(end - start);
    while(if_continue)
    {
        text.clear();
        end = system_clock::now(); //标记现在的时间
        now_time = duration_cast<ourtime>(end - start);//开始与现在的时间相减
        value = float(now_time.count()) * ourtime::period::num / ourtime::period::den + pass_time;//移动小数点位置, 使其符合习惯
        if(value - point_count < 0.1)
            continue;
        else
            point_count = value;
        if(int(point_count) - int_count >= 1)//终端的输出, 为整数
        {
            int_count = int(point_count);
            cout << int_count << endl;
        }
        temp = to_string(point_count);//浮点数转换为string, 暂时存放在temp中
        
        for(i = 0; temp[i] != '.'; i++)//把temp取到小数点后一位
            text += temp[i];
        text += '.';
        text += temp[++i];
        text += " s";

        putText(time_img, text, origin, FONT_HERSHEY_COMPLEX, 2.5, Scalar(255, 0, 255), 2, 8, 0);//图片上添加文本框
        imshow("Welcome!", time_img);
        waitKey(30);//等待30ms, 让图像显示
        time_img = imread("welcome.jpg");//重新读入图片
    }
}
void Timer::stopTiming()
{
    if_continue = false;
    this->open();
    waitKey(40);
}
void Timer::close()
{
    if_continue = false;
    destroyWindow("Welcome!");
}
void Timer::pause()
{
    if_continue = false;
}
void Timer::resume()
{
    if_continue = true;
}
float Timer::get_float()
{
    return point_count;
}