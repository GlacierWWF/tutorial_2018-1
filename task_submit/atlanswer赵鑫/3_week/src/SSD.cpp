#include "SSD.hpp"

SSD::SSD(char* originalImageUri) {
    originalImage = cv::imread(originalImageUri, cv::IMREAD_COLOR);
    playground();
}

void SSD::display(cv::Mat& image) {
    if (!image.data) {
        std::cout << "No image data." << std::endl;
    }

    cv::namedWindow(originalImageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(originalImageWindowName, image);

    cv::waitKey(0);
}

void SSD::save(cv::Mat& image) {
    cv::imwrite("./save1.jpg", image);
    std::cout << "saved.\n";
}

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

void SSD::threshold() {
    if (maxLoc > 175) {
        std::cout << "[info] Removing bright spots." << std::endl;
        cv::GaussianBlur(extracted, extracted, cv::Size(9, 9), 0);
        histrogram(extracted, true);
        if (maxLoc < 73) {
            cv::threshold(extracted, thresholded, 106, 255, cv::THRESH_BINARY);
        } else {
        cv::threshold(extracted, thresholded, maxLoc + 9, 255, cv::THRESH_BINARY);
        }
        /* cv::namedWindow("Thr", cv::WINDOW_AUTOSIZE);
        cv::imshow("Thr", thresholded);
        cv::waitKey(0); */
    } else {
        std::cout << "[info] Emphasizing LED segments." << std::endl;
        cv::GaussianBlur(extracted, extracted, cv::Size(9, 9), 0);
        histrogram(extracted, true);
        cv::threshold(extracted, thresholded, 190, 255, cv::THRESH_BINARY);
    
        /* cv::namedWindow("Thr1", cv::WINDOW_AUTOSIZE);
        cv::imshow("Thr1", thresholded);
        cv::waitKey(0); */
        // cv::GaussianBlur(thresholded, thresholded, cv::Size(11, 11), 0);
    }
}

void SSD::findContour() {
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2))};
    cv::morphologyEx(thresholded, erosion, cv::MORPH_OPEN, kernel);
    cv::threshold(erosion, erosion, 0, 255, cv::THRESH_OTSU);
    cv::Rect roi = cv::Rect(erosion.cols * 0.01, 
                            erosion.rows * 0.05, 
                            erosion.cols * 0.94,
                            erosion.rows * 0.9);
    std::vector<std::vector<cv::Point> > contours, filteredContours;
    std::vector<cv::Rect> boundingBoxes;
    cv::findContours(erosion(roi), contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE,
                     cv::Point(erosion.cols * 0.01,
                               erosion.rows * 0.05));
        /* cv::namedWindow("Cont", cv::WINDOW_AUTOSIZE);
        cv::imshow("Cont", thresholded);
        cv::waitKey(0); */
    
    for (size_t i{0}; i < contours.size(); ++i) {
        cv::Rect bounds = cv::boundingRect(contours[i]);
        if (bounds.x > erosion.cols * 0.01
            and bounds.area() > 300
            and (bounds.height > bounds.width * 1.5
                 or bounds.width > bounds.height * 1.5
                 or bounds.area() > 1800)) {
            boundingBoxes.push_back(bounds);
            filteredContours.push_back(contours[i]);
        }
    }

    /* for (size_t i{0}; i < boundingBoxes.size(); ++i) {
        cv::rectangle(erosion, boundingBoxes[i], cv::Scalar(150), 2);
    } */

    std::vector<cv::Point> outlines;
    for (size_t i{0}; i < filteredContours.size(); ++i) {
        outlines.insert(outlines.end(),
                        filteredContours[i].begin(),
                        filteredContours[i].end());
    }
    bounding = cv::minAreaRect(outlines);

    bounding.points(verticies);
    for (int i{0}; i < 4; ++i) {
        line(erosion, verticies[i], verticies[(i+1)%4],
             cv::Scalar(150), 2);
    }

        cv::namedWindow("box", cv::WINDOW_AUTOSIZE);
        cv::imshow("box", erosion);
        cv::waitKey(0);
}

void SSD::warp() {
    cv::Point2f dst[4];
    cv::Size size;
    bool ret{bounding.size.width > bounding.size.height};
    std::cout << bounding.size << std::endl;
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

    /* cv::namedWindow("warp1", cv::WINDOW_AUTOSIZE);
    cv::imshow("warp1", warpped);
    cv::waitKey(0); */
}

void SSD::readDigit() {
    // cv::Mat warpDigit{};
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 10))};
    cv::morphologyEx(warpped, warpped, cv::MORPH_DILATE, kernel);
    // cv::threshold(erosion, erosion, 0, 255, cv::THRESH_OTSU);

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
        if (boundingBoxes[i].height > boundingBoxes[i].width * 3) {
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
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 12 * 11,
                        boundingBoxes[i].y + boundingBoxes[i].height / 4))
            < 100) {
                if (warpped.at<uchar>(
            cv::Point2f(boundingBoxes[i].x + boundingBoxes[i].width / 8,
                        boundingBoxes[i].y + boundingBoxes[i].height / 12 * 11))
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
    cv::namedWindow("warp", cv::WINDOW_AUTOSIZE);
    cv::imshow("warp", warpped);
    cv::waitKey(0);

}

void SSD::playground() {
    extract();
    threshold();
    findContour();
    warp();
}

SSD2::SSD2(char* oimg1, char* oimg2):
    img1{new SSD(oimg1)}, img2{new SSD(oimg2)} {
    img1->playground();
    img2->playground();
    
}

void SSD2::combine() {
    combinedSize.width = (img1->warpped.cols + img2->warpped.cols) / 2;
    combinedSize.height = (img1->warpped.rows + img2->warpped.rows) / 2;

    cv::Point2f src1[4], src2[4], dst[4];
    src1[0] = cv::Point2f(0, img1->warpped.rows);
    src1[1] = cv::Point2f(0, 0);
    src1[2] = cv::Point2f(img1->warpped.cols, 0);
    src1[3] = cv::Point2f(img1->warpped.cols, img1->warpped.rows);
    src2[0] = cv::Point2f(0, img2->warpped.rows);
    src2[1] = cv::Point2f(0, 0);
    src2[2] = cv::Point2f(img2->warpped.cols, 0);
    src2[3] = cv::Point2f(img2->warpped.cols, img2->warpped.rows);
    dst[0] = cv::Point2f(0, combinedSize.height);
    dst[1] = cv::Point2f(0, 0);
    dst[0] = cv::Point2f(combinedSize.width, 0);
    dst[0] = cv::Point2f(combinedSize.width, combinedSize.height);

    cv::Mat img1Tran{}, img2Tran{};
    cv::Mat img1Dst{}, img2Dst{};
    img1Tran = cv::getAffineTransform(src1, dst);
    img2Tran = cv::getAffineTransform(src2, dst);
    cv::warpAffine(img1->warpped, img1Dst, img1Tran, combinedSize);

    cv::namedWindow("img1Dst", cv::WINDOW_AUTOSIZE);
    cv::imshow("img1Dst", img1Dst);
    cv::waitKey(0);
}