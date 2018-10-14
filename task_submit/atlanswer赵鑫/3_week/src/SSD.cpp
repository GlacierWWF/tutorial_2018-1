#include "SSD.hpp"

SSD::SSD(char* originalImageUri) {
    originalImage = cv::imread(originalImageUri, cv::IMREAD_COLOR);
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

void SSD::gaussianBlur() {
    cv::GaussianBlur(originalImage, blurred, cv::Size(7, 7), 0);
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
        cv::Mat BxG{};
        cv::addWeighted(channelBGR[0], 0.3, channelBGR[1], 0.3, 0, BxG);
        cv::subtract(channelBGR[2], BxG, extracted);
    } else {
        extracted = channelBGR[2].clone();
    }
}

void SSD::threshold() {
    if (maxLoc > 175) {
        cv::GaussianBlur(extracted, extracted, cv::Size(9, 9), 0);
        histrogram(extracted, true);
        if (maxLoc < 73) {
            cv::threshold(extracted, thresholded, 106, 255, cv::THRESH_BINARY);
        } else {
        cv::threshold(extracted, thresholded, maxLoc + 10, 255, cv::THRESH_BINARY);
        }
        cv::namedWindow("Thr", cv::WINDOW_AUTOSIZE);
        cv::imshow("Thr", thresholded);
        cv::waitKey(0);
    } else {
        histrogram(extracted, true);
        cv::threshold(extracted, thresholded, 180, 255, cv::THRESH_BINARY);
    
        cv::namedWindow("Thr1", cv::WINDOW_AUTOSIZE);
        cv::imshow("Thr1", thresholded);
        cv::waitKey(0);    
        // cv::GaussianBlur(thresholded, thresholded, cv::Size(11, 11), 0);
    }
}

void SSD::morphology() {
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2))};
    cv::morphologyEx(thresholded, erosion, cv::MORPH_ERODE, kernel);
    cv::threshold(erosion, erosion, 0, 255, cv::THRESH_OTSU);
}

void SSD::findContour() {
    cv::Rect roi = cv::Rect(erosion.cols * 0.08, 
                            erosion.rows * 0.05, 
                            erosion.cols * 0.84, 
                            erosion.rows * 0.95);
    std::vector<std::vector<cv::Point> > contours, filteredContours;
    std::vector<cv::Rect> boundingBoxes;
    cv::findContours(erosion(roi), contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE,
                     cv::Point(erosion.cols * 0.08,
                               erosion.rows * 0.05));
        cv::namedWindow("Cont", cv::WINDOW_AUTOSIZE);
        cv::imshow("Cont", thresholded);
        cv::waitKey(0);
    
    for (size_t i{0}; i < contours.size(); ++i) {
        cv::Rect bounds = cv::boundingRect(contours[i]);
        if (bounds.x > erosion.cols * 0.08
            and bounds.area() > 200
            and (bounds.height > bounds.width * 1.5
                 or bounds.width > bounds.height * 1.5
                 or bounds.area() > 2000)) {
            boundingBoxes.push_back(bounds);
            filteredContours.push_back(contours[i]);
        }
    }

    /* std::sort(boundingBoxes.begin(), boundingBoxes.end(),
              [](cv::Rect& a, cv::Rect& b) {
                  return a.x < b.x;
              }); */

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

}

void SSD::playground() {
    // gaussianBlur();
    extract();
    threshold();
    // rotate(detectSkew());
    morphology();
    findContour();

}