/*****************************************************************************
*  Seven-segment display ocr program                                         *
*                                                                            *
*  @file     SSD.hpp                                                         *
*  @brief    SSD class header file                                           *
*                                                                            *
*  @author   atlanswer                                                       *
*  @email    atlanswer@gmail.com                                             *
*  @version  Beta-2                                                          *
*  @date     10/20/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/20 | Beta-2   | atlanswer      | Complete mission                 *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

//Standard I/O
#include <iostream>
//Math operation
#include <cmath>
//OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/**
    * @brief Class for processing a stand-alone image
    */
class SSD {
        std::string originalImageWindowName {
            "Original image"
        };
        void histrogram(cv::Mat&, bool);
        void extract();
        void threshold();
        void findContour();
        void warp();

    protected:
        cv::Mat originalImage{};
        cv::Mat equalized{};
        cv::Mat blurred{};
        cv::Mat extracted{};
        int maxLoc;
        cv::Mat thresholded{};
        cv::Mat erosion{};
        cv::RotatedRect bounding{};
        cv::Point2f verticies[4];
        std::vector<int> answer{};

    public:
        SSD(char*);
        cv::Mat warpped{};
        void playground();
        void readDigit();

};