/*
    This .hpp file is used to creat a test matrix.
    
    author: ZhangHaoxuan
    last edit: 2018-10-13
    version: 1.0.0
*/

#ifndef _MATRIX_H_
#define _MATRIX_H_
#include"opencv2/opencv.hpp"
#include<iostream>
#include<vector>
#include<fstream>
#define pix_row 64
#define pix_col 32
#define debug
using namespace std;
using namespace cv;

class matrix
{
    public:
    /*
    * @brief: 测试数据
    */
    vector<vector<int> >test_matrix;

    matrix();

    /*
    * @brief: 测试矩阵读取已经存在txt中的数据
    */
    void test_read();

    /*
    * @brief: 测试数据与读取数据进行对比, 识别数字
    */
    int compare(vector<vector<int> > &, int );

};

#endif