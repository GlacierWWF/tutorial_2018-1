/**
 * @file main.cpp
 * @atlanswer (atlanswer@gmail.com)
 * @brief Optical flow main program
 * @version debug
 * @date 2018-11-11
 * 
 */

#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "OpticalFlowPX4.hpp"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    float FOCAL_LENGTH_X{13};
    float FOCAL_LENGTH_Y{7};
    const int IMG_WIDTH{1280};
    const int IMG_HEIGHT{720};
    const int SEARCH_SIZE{110};
    const int FPS{10};
    Point center(IMG_WIDTH / 2, IMG_HEIGHT / 2);

    if (!cap.isOpened()) {
        CV_Assert("Camera open failed.");
        return -1;
    }

    OpticalFlowPX4 flow(FOCAL_LENGTH_X, FOCAL_LENGTH_Y, FPS, IMG_WIDTH, IMG_HEIGHT, SEARCH_SIZE);

    Mat frame{};
    uint8_t* imgCurrent;
    uint32_t timeStamp{0};
    int deltaT{};
    float flowX{}, flowY{};

    namedWindow("Camera", WINDOW_AUTOSIZE);
    for (;;) {
        // get a video frame and preprocess it
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Mat oneD = frame.reshape(1, 1);
        imgCurrent = oneD.data;

        // angular flow
        Point angularX(center);
        Point angularY(center);

        flow.calcFlow(imgCurrent, timeStamp, deltaT, flowX, flowY);
        angularX.x += 1000 * flowX;
        angularY.y += 1000 * flowY;
        line(frame, center, angularX, Scalar(90), 5);
        line(frame, center, angularY, Scalar(180), 5);

        imshow("Camera", frame);
        timeStamp += 10000;
        cout << "Flow X: " << flowX << ", Flow Y: " << flowY << endl;
        if(waitKey(100) >= 0) break;
    }

    return 0;
}