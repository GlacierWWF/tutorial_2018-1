//
//  main.cpp
//  SIFT
//
//  Created by 张涵健 on 2018/11/7.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//


#include "../include/SIFT.hpp"
//#include "opencv2/feature2d.hpp"

//using namespace std;
void sort(vector<KeyPoint> &key_points){
    vector<KeyPoint>::iterator a = key_points.begin();
    for (int i = 0; i < key_points.size()-1; i++){
        for(int j = 0; j < key_points.size()-1-i; j++){
            if ((a+j)->size < (a+j+1)->size){
                KeyPoint tmp = *(a+j);
                *(a+j) = *(a+j+1);
                *(a+j+1) = tmp;
            }
        }
    }
}

int main(int argc, char** argv)
{
    string s1,s2;
    cout << "Input two pictures with relative path:" << endl;
    cin >> s1 >> s2;
    Mat img = imread(s1);
    Mat img2 = imread(s2);
    resize(img2, img2, img.size());

    SIFT sift;    //实例化SIFT类

    vector<KeyPoint> key_points;    //特征点
    vector<KeyPoint> key_points2;
    // descriptors为描述符，mascara为掩码矩阵
    Mat descriptors, mascara;
    Mat descriptors2, mascara2;
    Mat output_img;    //输出图像矩阵
    Mat output_img2;
    //int max = 0;
    sift(img,mascara,key_points,descriptors);//执行SIFT运算
    sift(img2,mascara2,key_points2,descriptors2);
    //imshow("123", descriptors);
    //waitKey(1);

     drawKeypoints(img,              //输入图像
     key_points,      //特征点矢量
     output_img,      //输出图像
     Scalar::all(-1),      //绘制特征点的颜色，为随机
     //以特征点为中心画圆，圆的半径表示特征点的大小，直线表示特征点的方向
     DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    drawKeypoints(img2,              //输入图像
                  key_points2,      //特征点矢量
                  output_img2,      //输出图像
                  Scalar::all(-1),      //绘制特征点的颜色，为随机
                  //以特征点为中心画圆，圆的半径表示特征点的大小，直线表示特征点的方向
                  DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    //namedWindow("SIFT");
    imshow("SIFT", output_img);
    waitKey(1);
    imshow("SIFT2", output_img2);
    waitKey(1);
    for (vector<KeyPoint>::iterator a = key_points.begin(); a != key_points.end();){
        if (a->size < 15){
            a = key_points.erase(a);
        }
        else
            a++;
    }
    for (vector<KeyPoint>::iterator a = key_points2.begin(); a != key_points2.end();){
        if (a->size < 15){
            a = key_points2.erase(a);
        }
        else{
            //a->pt.x += img.cols;
            a++;
        }
    }
    sift(img,mascara,key_points,descriptors,true);//执行SIFT运算
    sift(img2,mascara2,key_points2,descriptors2,true);
    //cout << max;
    //cout << (key_points[0]<key_points2[0]);
    //sort(key_points,key_points,1);
    //sort(key_points2,key_points2,1);

    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;
    matcher.match(descriptors, descriptors2, matches);
    Mat result;
    drawMatches(img, key_points, img2, key_points2, matches, result);
    /*
    FlannBasedMatcher matcher;
    vector<vector<DMatch> > matchePoints;
    vector<DMatch> GoodMatchePoints;
    vector<Mat> train_desc(10, descriptors);
    matcher.add(train_desc);
    matcher.train();

    matcher.knnMatch(descriptors2, matchePoints, 30);
    for (int i = 0; i < matchePoints.size(); i++)
    {
        if (matchePoints[i][0].distance < 0.7 * matchePoints[i][1].distance)
        {
            GoodMatchePoints.push_back(matchePoints[i][0]);
        }
    }
    drawMatches(img, key_points, img2, key_points2, GoodMatchePoints, output_img);
*/
    //在输出图像中绘制特征点

/*
    sort(key_points);
    sort(key_points2);
    RNG rng(time(0));
    output_img.copyTo(img);
    output_img2.copyTo(img2);
    Mat combine(img.rows, img.cols*2, img.type());
    img.colRange(0, img.cols).copyTo(combine.colRange(0, img.cols));
    img2.colRange(0, img2.cols).copyTo(combine.colRange(img.cols, combine.cols));
    for (int i = 0 ; i != key_points.size(); i++){

        vector<KeyPoint>::iterator a = key_points.begin();
        vector<KeyPoint>::iterator b = key_points2.begin() + i;
        if ( abs(b->size - (a+i)->size)/((b->size + (a+i)->size)/2) < 0.2){
            line(combine, (a+i)->pt, b->pt, cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)));
        }

    }
 */
    imshow("result", result);
    waitKey(1000000000);
    return 0;
}
