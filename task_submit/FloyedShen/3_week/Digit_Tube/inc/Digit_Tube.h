/*********************************************************
 * Digit_Tube image Recognition by opencv
 *
 * @author	Floyed_Shen
 * @email	Floyed_Shen@outlook.com
 * @version	1.0.0
 * @date	2018/10/12
 *********************************************************/
#ifndef DIGIT_TUBE
#define DIGIT_TUBE
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


class Digit_Tube{
    private:
        int model;//0为输入一张图片，1为输入2张图片
        int x,y,z_ero,z_dil,g;//置换矩阵/高斯核的参数
        cv::Mat mt,bin,red,green,blue;//储存图像
        cv::Mat comb1,comb2,bin1,bin2;//输入两张图片
        std::vector<int>ans;//储存识别答案的数组
        std::vector<cv::Mat>num;//数字分割之后的图片
        std::vector<bool>digit_res[4];//储存每个数码管对应的每个管子的值
        float calc_bin(cv::Mat)const;//计算二值化图像中0的占比
        friend bool cmp_area(cv::Rect,cv::Rect);//服务于sort，排序按照面积
        friend bool cmp_height(cv::Rect,cv::Rect);//sort，高度
        friend bool cmp_tl(cv::Rect,cv::Rect);//sort，起点横坐标
        friend bool cmp_dis1(cv::Point2f ,cv::Point2f);//距离原点的一维模值
        void rotate(cv::Mat &);//透视旋转
        void add();//用于两个图像，二值化之后加和
        void pre_solve(cv::Mat&);//预处理，分成RGB通道，并调用gray_bin()
        void gray2bin();//腐蚀膨胀、二值化，并将RGB通道评估并合成
        void img_divide();//图像分割、生成vector::num
        void num_divide();//对每个数字分割 生成 digit_res
        void translate();//转译 digit_res —> ans

    public:
        Digit_Tube();//初始化
        Digit_Tube(cv::Mat);//
        Digit_Tube(char[]);//
        Digit_Tube(std::string );//
        Digit_Tube(std::string,std::string);//
        bool open()const;//判断是否打开图像
        void identify();//图像识别
        void print()const;//打印ans
        ~Digit_Tube();//
};
#endif