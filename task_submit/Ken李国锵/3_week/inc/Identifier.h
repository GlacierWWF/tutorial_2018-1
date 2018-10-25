/***************************************
 * **Identifier.h
 * Author:Ken李国锵
 * Date:2018/10/10
 * Version:1.0.0
 * Abstract:
 * *************************************/

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//BINARY
void BinImg(Mat &, int);

//VECTOR
void VecImg(vector<vector<int>>&, Mat &, int);

//Contour Cleaning
void CleanCon(vector<vector<Point>> &);

//SORT
vector<Rect> sort_rec(vector<vector<Point>> &);

//GAUSS FILTER
void gauss(Mat &);

//PRE PROCESSING
void prepro(Mat &);

//FIND MEDIAN
int find_median(const vector<Rect>, int);

//SIZE UNIFORMING
void uniform_size(vector<Mat> &, vector<Mat> &);

//IDENTIFIER
void Identifier(int , char*[]);

//ROTATE
void ifRotate(vector<Mat> &, vector<Rect> &);

#endif


