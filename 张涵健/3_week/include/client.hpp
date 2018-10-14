//
//  client.hpp
//  Digit_discern
//
//  Created by 张涵健 on 2018/10/8.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#ifndef client_hpp
#define client_hpp

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#define OW 7
#define WD 20
using namespace cv;
using namespace std;

struct Con {
    double x = 0, y = 0;
    int order = 0;

    bool operator < (const Con &m) const{
        if (x < m.x) return true;
        else if(x == m.x){
            if(y < m.y) return true;
        }
        return false;
    }
};

struct Result {
    double bi;
    int num;

    bool operator < (const Result &m) const{
        return (bi < m.bi);
     }
};

class  client{
private:
    string src_name;
    Mat num[15];
    Con con[100];
    Result _result[15];
    double compare(Mat &src, Mat &sample);
    void Threshold(Mat &src,Mat &sample,int m);
    void deal(Mat &src,int order);
    void take_red(Mat &src, int r_level, int b_level, int g_level);
    Mat combine(Mat&, Mat&);
    double filter_har(Mat src)
    {
        double har=0;
        for (int i =0;i < src.rows;i++ ){
            uchar* data=src.ptr<uchar>(i);
            for (int j =0;j <src.cols;j++){
                if (data[j]!=0) har+=1/(double)(data[j]);
            }
        }
        return (src.cols*src.rows)/har;
    }
    Mat filter(Mat image, Size size);
public:
    client();
    void open(string);
    void test_1();  /* test level 1 */
    void test_2();  /* test level 2 */
    void test_3(string ,string);  /* test level 3 */
    void test();
};


#endif /* client_hpp */
