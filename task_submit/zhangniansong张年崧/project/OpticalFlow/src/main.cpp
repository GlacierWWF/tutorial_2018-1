#include "opencv2/video/tracking.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

#define ATD at<double>
#define elif else if

#ifndef bool
    #define bool int
    #define false ((bool)0)
    #define true  ((bool)1)
#endif


Mat get_fx(Mat &src1, Mat &src2){
    Mat fx;
    Mat kernel = Mat::ones(2, 2, CV_64FC1);
    kernel.ATD(0, 0) = -1.0;
    kernel.ATD(1, 0) = -1.0;

    Mat dst1, dst2;
    filter2D(src1, dst1, -1, kernel);
    filter2D(src2, dst2, -1, kernel);

    fx = dst1 + dst2;
    return fx;
}

Mat get_fy(Mat &src1, Mat &src2){
    Mat fy;
    Mat kernel = Mat::ones(2, 2, CV_64FC1);
    kernel.ATD(0, 0) = -1.0;
    kernel.ATD(0, 1) = -1.0;

    Mat dst1, dst2;
    filter2D(src1, dst1, -1, kernel);
    filter2D(src2, dst2, -1, kernel);

    fy = dst1 + dst2;
    return fy;
}

Mat get_ft(Mat &src1, Mat &src2){
    Mat ft;
    Mat kernel = Mat::ones(2, 2, CV_64FC1);
    kernel = kernel.mul(-1);

    Mat dst1, dst2;
    filter2D(src1, dst1, -1, kernel);
    kernel = kernel.mul(-1);
    filter2D(src2, dst2, -1, kernel);

    ft = dst1 + dst2;
    return ft;
}

bool isInsideImage(int y, int x, Mat &m){
    int width = m.cols;
    int height = m.rows;
    if(x >= 0 && x < width && y >= 0 && y < height) return true;
    else return false;
}

double get_Sum9(Mat &m, int y, int x){
    if(x < 0 || x >= m.cols) return 0;
    if(y < 0 || y >= m.rows) return 0;

    double val = 0.0;
    int tmp = 0;
    if(isInsideImage(y - 1, x - 1, m)){
        ++ tmp;
        val += m.ATD(y - 1, x - 1);
    }
    if(isInsideImage(y - 1, x, m)){
        ++ tmp;
        val += m.ATD(y - 1, x);
    }
    if(isInsideImage(y - 1, x + 1, m)){
        ++ tmp;
        val += m.ATD(y - 1, x + 1);
    }
    if(isInsideImage(y, x - 1, m)){
        ++ tmp;
        val += m.ATD(y, x - 1);
    }
    if(isInsideImage(y, x, m)){
        ++ tmp;
        val += m.ATD(y, x);
    }
    if(isInsideImage(y, x + 1, m)){
        ++ tmp;
        val += m.ATD(y, x + 1);
    }
    if(isInsideImage(y + 1, x - 1, m)){
        ++ tmp;
        val += m.ATD(y + 1, x - 1);
    }
    if(isInsideImage(y + 1, x, m)){
        ++ tmp;
        val += m.ATD(y + 1, x);
    }
    if(isInsideImage(y + 1, x + 1, m)){
        ++ tmp;
        val += m.ATD(y + 1, x + 1);
    }
    if(tmp == 9) return val;
    else return m.ATD(y, x) * 9;
}

Mat get_Sum9_Mat(Mat &m){
    Mat res = Mat::zeros(m.rows, m.cols, CV_64FC1);
    for(int i = 1; i < m.rows - 1; i++){
        for(int j = 1; j < m.cols - 1; j++){
            res.ATD(i, j) = get_Sum9(m, i, j);
        }
    }
    return res;
}

void saveMat(Mat &M, string s){
    s += ".txt";
    FILE *pOut = fopen(s.c_str(), "w+");
    for(int i=0; i<M.rows; i++){
        for(int j=0; j<M.cols; j++){
            fprintf(pOut, "%lf", M.ATD(i, j));
            if(j == M.cols - 1) fprintf(pOut, "\n");
            else fprintf(pOut, " ");
        }
    }
    fclose(pOut);
}

void getLucasKanadeOpticalFlow(Mat &img1, Mat &img2, Mat &u, Mat &v, Mat &dx, Mat &dy){

    Mat fx = get_fx(img1, img2);
    Mat fy = get_fy(img1, img2);
    Mat ft = get_ft(img1, img2);

    Mat fx2 = fx.mul(fx);
    Mat fy2 = fy.mul(fy);
    Mat fxfy = fx.mul(fy);
    Mat fxft = fx.mul(ft);
    Mat fyft = fy.mul(ft);

    Mat sumfx2 = get_Sum9_Mat(fx2);
    Mat sumfy2 = get_Sum9_Mat(fy2);
    Mat sumfxft = get_Sum9_Mat(fxft);
    Mat sumfxfy = get_Sum9_Mat(fxfy);
    Mat sumfyft = get_Sum9_Mat(fyft);

    Mat tmp = sumfx2.mul(sumfy2) - sumfxfy.mul(sumfxfy);
    u = sumfxfy.mul(sumfyft) - sumfy2.mul(sumfxft);
    v = sumfxft.mul(sumfxfy) - sumfx2.mul(sumfyft);
    divide(u, tmp, u);
    divide(v, tmp, v);

//    saveMat(u, "U");
//    saveMat(v, "V");   
    dx = -fx.mul(u);
    dy = -fy.mul(v);
}


int main()
{
    VideoCapture cap(0);
    if( !cap.isOpened() )
        return -1;
    
    Mat flow, cflow, frame;
    Mat gray, prevgray;
    namedWindow("flow", CV_WINDOW_NORMAL);

    while(1)
    {
        cap >> frame;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        Mat canvas = frame.clone();

        if ( !prevgray.empty() )
        {
            prevgray.convertTo(prevgray, CV_64FC1, 1.0/255, 0);
            gray.convertTo(gray, CV_64FC1, 1.0/255, 0);

            Mat u = Mat::zeros(prevgray.cols, prevgray.rows, CV_64FC1);
            Mat v = Mat::zeros(prevgray.cols, prevgray.rows, CV_64FC1);

            Mat dx = Mat::zeros(prevgray.cols, prevgray.rows, CV_64FC1);
            Mat dy = Mat::zeros(prevgray.cols, prevgray.rows, CV_64FC1);
            
            getLucasKanadeOpticalFlow(prevgray, gray, u, v, dx, dy);

            Mat I = Mat(u.cols, u.rows, CV_32FC1);
            
            for(int x=0; x < canvas.cols-100; x += 100)
            {
                for (int y=0; y < canvas.rows-100; y += 100)
                {
                    line(canvas, Point(x,y), Point(x +  dx.at<double>(x,y)*10, y + dy.at<double>(x,y)*10), Scalar(0,255,0), 2);
                }
            }
            imshow("flow", canvas);
            //imshow("flow", It);
            //imshow("flow", frame);
            I = (dx*0.1).mul(dx*0.1) + (dy*0.1).mul(dy*0.1);
            pow(I, 0.5, I);
            cout << sum(I)[0] << endl;
            //cout << "\033[2J\033[1;1H";
            
        }
        if(waitKey(30) >= 0)
            break;

        std::swap(prevgray, gray);
    }

    return 0;
}