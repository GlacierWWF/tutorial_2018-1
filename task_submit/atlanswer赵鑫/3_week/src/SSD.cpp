/*****************************************************************************
*  Seven-segment display ocr program                                         *
*                                                                            *
*  @file     SSD.cpp                                                         *
*  @brief    SSD class source file                                           *
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

#include "SSD.hpp"


/** 
    * @brief SSD class constructor
    * @param originalImageUri char*  
    */
SSD::SSD(char* originalImageUri) {
    originalImage = cv::imread(originalImageUri, cv::IMREAD_COLOR);
    if (!originalImage.data)
        std::cout << "[Error] Image not found   ." << std::endl;
    playground();
}

/** 
    * @brief Calculate histrogram
    * @param channel cv::Mat&
    * @param thresh bool
    */
void SSD::histrogram(cv::Mat& channel, bool thresh) {
    int histSize{256};
    float range[]{0, 256};
    const float* histRange{range};
    cv::Mat histrogramed{};

    cv::calcHist(&channel, 1, 0, cv::noArray(),
                 histrogramed, 1, &histSize, &histRange);

    if (thresh)
        cv::GaussianBlur(histrogramed, histrogramed, cv::Size(9, 9), 0);
    
    cv::minMaxIdx(histrogramed, NULL, NULL, NULL, &maxLoc);
}

/** 
    * @brief Extract ROI
    */
void SSD::extract() {
    cv::Mat channelBGR[3];
    cv::split(originalImage, channelBGR);

    histrogram(channelBGR[2], false);

    if (maxLoc > 175) {
        std::cout << "[info] The image is overexposed." << std::endl;
        cv::Mat BxG{};
        cv::addWeighted(channelBGR[0], 0.3, channelBGR[1], 0.3, 0, BxG);
        cv::subtract(channelBGR[2], BxG, extracted);
    } else {
        std::cout << "[info] The image exposure is normal." << std::endl;
        extracted = channelBGR[2].clone();
    }
}

/** 
    * @brief Binarization
    */
void SSD::threshold() {
    if (maxLoc > 175) {
        std::cout << "[info] Removing bright spots." << std::endl;
        cv::GaussianBlur(extracted, extracted, cv::Size(9, 9), 0);
        histrogram(extracted, true);
        if (maxLoc < 73) {
            cv::threshold(extracted, thresholded, 106, 255, cv::THRESH_BINARY);
        } else {
        cv::threshold(extracted, thresholded, maxLoc + 10, 255, cv::THRESH_BINARY);
        }
    } else {
        std::cout << "[info] Emphasizing LED segments." << std::endl;
        cv::GaussianBlur(extracted, extracted, cv::Size(9, 9), 0);
        histrogram(extracted, true);
        cv::threshold(extracted, thresholded, 195, 255, cv::THRESH_BINARY);
    }
}

/** 
    * @brief Locate segments
    */
void SSD::findContour() {
    cv::Mat kernelE{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4))};
    cv::Mat kernelD{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(8, 8))};
    cv::morphologyEx(thresholded, erosion, cv::MORPH_ERODE, kernelE);
    cv::morphologyEx(erosion, erosion, cv::MORPH_DILATE, kernelD);
    cv::threshold(erosion, erosion, 0, 255, cv::THRESH_OTSU);
    cv::Rect roi = cv::Rect(erosion.cols * 0.04, 
                            erosion.rows * 0.05, 
                            erosion.cols * 0.92,
                            erosion.rows * 0.9);
    std::vector<std::vector<cv::Point> > contours, filteredContours;
    std::vector<cv::Rect> boundingBoxes;
    cv::findContours(erosion(roi), contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE,
                     cv::Point(erosion.cols * 0.04,
                               erosion.rows * 0.05));
    
    for (size_t i{0}; i < contours.size(); ++i) {
        cv::Rect bounds = cv::boundingRect(contours[i]);
        if (bounds.x > erosion.cols * 0.04
            and bounds.area() > 300
            and (bounds.height > bounds.width * 1.5
                 or bounds.width > bounds.height * 1.5
                 or bounds.area() > 1800)) {
            boundingBoxes.push_back(bounds);
            filteredContours.push_back(contours[i]);
        }
    }

    for (size_t i{0}; i < boundingBoxes.size(); ++i) {
        cv::rectangle(erosion, boundingBoxes[i], cv::Scalar(150), 2);
    }

    std::vector<cv::Point> outlines;
    for (size_t i{0}; i < filteredContours.size(); ++i) {
        outlines.insert(outlines.end(),
                        filteredContours[i].begin(),
                        filteredContours[i].end());
    }
    bounding = cv::minAreaRect(outlines);

    bounding.points(verticies);
    for (int i{0}; i < 4; ++i) {
        line(originalImage, verticies[i], verticies[(i+1)%4],
             cv::Scalar(150), 2);
    }

    cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original image", originalImage);
}

/** 
    * @brief Image correction
    */
void SSD::warp() {
    cv::Point2f dst[4];
    cv::Size size;
    bool ret{bounding.size.width > bounding.size.height};
    size.width = ret ? bounding.size.width : bounding.size.height;
    size.height = ret ? bounding.size.height : bounding.size.width;

    if (ret) {
        dst[0] = cv::Point2f(0, size.height);
        dst[1] = cv::Point2f(0, 0);
        dst[2] = cv::Point2f(size.width, 0);
        dst[3] = cv::Point2f(size.width, size.height);
    } else {
        dst[1] = cv::Point2f(0, size.height);
        dst[2] = cv::Point2f(0, 0);
        dst[3] = cv::Point2f(size.width, 0);
        dst[0] = cv::Point2f(size.width, size.height);
    }
    cv::Mat warpMat = cv::getAffineTransform(verticies,
                                             dst);
    cv::warpAffine(thresholded, warpped, warpMat, size);
}

/** 
    * @brief Extract digit
    */
void SSD::readDigit() {
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 10))};
    cv::morphologyEx(warpped, warpped, cv::MORPH_DILATE, kernel);

    std::vector<std::vector<cv::Point> > contours, filteredContours;
    std::vector<cv::Rect> boundingBoxes;
    cv::findContours(warpped, contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE);
    
    if (contours.size() > 4) {
        cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15))};
        cv::morphologyEx(warpped, warpped, cv::MORPH_DILATE, kernel);
        cv::findContours(warpped, contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE);
    }

    for (size_t i{0}; i < contours.size(); ++i) {
        boundingBoxes.push_back(cv::boundingRect(contours[i]));
        cv::rectangle(warpped, boundingBoxes[i],
                      cv::Scalar(150), 2);
    }

    std::sort(boundingBoxes.begin(), boundingBoxes.end(),
              [](cv::Rect& a, cv::Rect& b) {
                  return a.x < b.x;
              });

    std::cout << "Answer: ";
    for (size_t i{0}; i < boundingBoxes.size(); ++i) {
        if (boundingBoxes[i].height > boundingBoxes[i].width * 2.5) {
            answer.push_back(1);
        }
        else if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 2,
                        boundingBoxes[i].y + boundingBoxes[i].height / 11))
            < 100) {
            answer.push_back(4);
        } else if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 2,
                        boundingBoxes[i].y + boundingBoxes[i].height / 2))
            < 100) {
                if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 8,
                        boundingBoxes[i].y + boundingBoxes[i].height / 8 * 6))
            < 100) {
                answer.push_back(7);
            } else {
                answer.push_back(0);
            }
        } else if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 8,
                        boundingBoxes[i].y + boundingBoxes[i].height / 8 * 2))
            < 100) {
                if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 8,
                        boundingBoxes[i].y + boundingBoxes[i].height / 8 * 6))
            < 100) {
                answer.push_back(3);
            } else {
                answer.push_back(2);
            }
        } else if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 14 * 13,
                        boundingBoxes[i].y + boundingBoxes[i].height / 4))
            < 100) {
                if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 9,
                        boundingBoxes[i].y + boundingBoxes[i].height / 4 * 3))
            < 100) {
                answer.push_back(5);
            } else {
                answer.push_back(6);
            }
        } else if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 8,
                        boundingBoxes[i].y + boundingBoxes[i].height / 8 * 6))
            < 100) {
                answer.push_back(9);
            } else {
                answer.push_back(8);
        }
    }

    for (int i{0}; i < 4; ++i)
        std::cout << answer[i];
    std::cout << std::endl;
    cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);
    cv::imshow("Result", warpped);
    cv::waitKey(0);
}

/** 
    * @brief Test function
    */
void SSD::playground() {
    extract();
    threshold();
    findContour();
    warp();
}