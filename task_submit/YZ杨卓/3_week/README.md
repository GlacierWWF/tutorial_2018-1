# Main function for SYSU-SWITF Tutorial Project

___
- **Author**: 杨卓
- **Revised**: 杨卓
- **Version**: 1.0.0
- **Date**: 2018-10-14
- **Abstract**: 使用opencv对数码管数字进行识别
___

## Required

For Unix/Linux:

- gcc >=3.0
- opencv >= 3.0

___

## Description

---

- ### Functions:

      void filteredRed(const Mat &inputImage, Mat &resultGray);    //用于从从原始图像中提取数字图像

      bool cmp(Rect& a, Rect& b)     { return (a.x < b.x) };     //用于数字轮廓排序

      int num_recognition(Mat img);     //输出识别的数字

      int num_judge(int count, Mat img);    //建立count和数字的对应关系，输出数字


- ### Depend Libraries:

        opencv required

- ### Compile:

        cmake .

        make

- ### Run:

        ./main  picture1
        
        或者

       ./main  picture1  picture2

---------


