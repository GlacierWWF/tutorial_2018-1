
/***********************************************************************
*
*  
*
*  @file       tell_digital.h
*  @brief      图像识别的头文件
*
*
*  @author     马飞鹏
*  @email      767102280@qq.com
*  @version    1.0.0
*  @date       2018/10/14
*
*
*  ------------------------------------------------------------
*  修改历史：
*  ------------------------------------------------------------
*  <日期>    |  <版本> |  <作者>  |  <描述>
*  ------------------------------------------------------------
*  2018/10/14 |  1.0.0  |  马飞鹏  | 创建文件
*  ------------------------------------------------------------
*  2018/10/15 |  1.0.1  |  马飞鹏  | 添加函数cut_picture(Mat &picture)
*  ------------------------------------------------------------
*/

#ifndef _TELL_DIGITAL_H
#define _TELL_DIGITAL_H

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;
int cut_picture(Mat &picture);///切割出合适的数字图像
int tell_num(Mat picture); ///识别数字
#endif
