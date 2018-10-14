#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

void hard(char* arg1, char* arg2, Mat& image_gry, bool& ifGamma, bool& isRecify); // funtion hard takes in two strings and returns a Mat
void simple(Mat& image_org, Mat& image_gry, bool& ifGamma); // function simple takes in a Mat and returns a Mat
void actual(Mat& image_org, Mat& image_gry, bool& isRecify); // function actual takes in a Mat and returns a Mat

void MyGammaCorrection(Mat& src, Mat& dst, float fGamma);


#endif