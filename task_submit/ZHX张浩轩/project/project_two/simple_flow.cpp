#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp" 
#include "opencv2/objdetect/objdetect.hpp" 
#include "opencv2/video/tracking.hpp" 
#include <vector> 
#include <stdio.h> 
#include <iostream>

using namespace std;
using namespace cv;

int abs(int a)
{
    return a >= 0? a: -a;
}

int main()
{
    VideoCapture cap(0);

    Mat flow, frame;

    /**
     * @如果可能, 则实现GPU加速
     */
    UMat flowUmat, prevgray;
    while(true)
    {
        /**
         * @摄像头打开失败
         */
        if(!cap.grab())
        {
            cout << "Capture open fail" << endl;
            break;
        }

        /**
         * @捕捉图像
         */
        Mat img;
        Mat original;
        cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
        resize(img, img, Size(720, 480));
        img.copyTo(original);
        cvtColor(img, img, COLOR_BGR2GRAY);
        if(prevgray.empty() == false)
        {
            /**
             * @调用opencv函数对前后两张灰度图进行光流计算
             */
            calcOpticalFlowFarneback(prevgray, img, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
            flowUmat.copyTo(flow);

            int x, y;
            int sum_x = 0, sum_y = 0;;
            Point temp;
            for(y = 0; y < original.rows; y+=5)
            {
                for(x = 0; x < original.cols; x+=5)
                {
                    const Point2f flowatxy = flow.at<Point2f>(y, x) * 2;
                    /**
                     * @绘制直线
                     */
                    temp = Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y));
                    line(original, Point(x, y), temp, Scalar(0, 0, 0));
                    sum_x += abs(temp.x - x);
                    sum_y += abs(temp.y - y);
                }
            }
            imshow("Simple_flow", original);
            cout << "Average_x:\t Average_y:" << endl;
            cout << sum_x << "\t\t" << sum_y << endl;
        }

        img.copyTo(prevgray);
        waitKey(20);
    }
}