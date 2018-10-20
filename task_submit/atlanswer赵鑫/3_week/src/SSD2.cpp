#include "SSD2.hpp"

SSD2::SSD2(char* pImg) {
    std::cout << "[info] Reading one image..." << std::endl;
    
    Img1 = new SSD0(pImg);

    condense();
}

SSD2::SSD2(char* pImg1, char* pImg2) {
    std::cout << "[info] Reading two images..." << std::endl;

    Img1 = new SSD0(pImg1);
    Img2 = new SSD0(pImg2);

    amalgamate();
}

void SSD2::condense() {
    cv::Point2f vImg[4];
    cv::Mat oImg{Img1->oImg};
    cv::Mat cImg;
    cv::RotatedRect bImg{Img1->extract()};

    bImg.points(vImg);
    for (int i{0}; i< 4; ++i)
        line(oImg, vImg[i], vImg[(i+1)%4], cv::Scalar(150), 2);

    cv::imshow("Bounding Box", oImg);
    cv::waitKey(0);
}

void SSD2::amalgamate() {
    cv::Point2f vImg1[4], vImg2[4];
    cv::Mat oImg1{Img1->oImg}, oImg2{Img2->oImg};
    cv::Mat cImg1, cImg2;
    cv::RotatedRect bImg1{Img1->extract()}, bImg2{Img2->extract()};

    bImg1.points(vImg1);
    bImg2.points(vImg2);
    for (int i{0}; i < 4; ++i) {
        line(oImg1, vImg1[i], vImg1[(i+1)%4], cv::Scalar(150), 2);
        line(oImg2, vImg2[i], vImg2[(i+1)%4], cv::Scalar(150), 2);
    }

    cv::imshow("ext", oImg1);
    cv::imshow("ext2", oImg2);

    cv::warpAffine(Img1->eImg, cImg1, Img1->transform, cv::Size(460, 160));
    cv::warpAffine(Img2->eImg, cImg2, Img2->transform, cv::Size(460, 160));

    cv::add(cImg1, cImg2, combineArm);
}

void SSD2::readDigit() {
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 27))};
    cv::Mat recog;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Rect> boundingBoxes;
    std::vector<int> answer;

    cv::morphologyEx(combineArm, recog, cv::MORPH_DILATE, kernel);
    cv::findContours(recog, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (auto cont:contours)
        boundingBoxes.push_back(cv::boundingRect(cont));
    std::sort(boundingBoxes.begin(), boundingBoxes.end(),
              [](cv::Rect& a, cv::Rect& b) {
                  return a.x < b.x;
              });
    for (auto box:boundingBoxes)
        cv::rectangle(combineArm, box, cv::Scalar(150), 2);

    cv::imshow("comb", combineArm);
    cv::imshow("reco", recog);

    for (auto box:boundingBoxes) {
        std::cout << box.width << ' ' << box.height << std::endl;
        //Determine 1
        if (box.height > box.width * 3) {
            answer.push_back(1);
        }
        //Segment in center
        else if (recog.at<uchar>(
            cv::Point2f(box.x + box.width / 2, box.y + box.height / 2)
        ) < 100) {
            //0 or 7
            if (recog.at<uchar>(
                cv::Point2f(box.x + box.width / 2, box.y + box.height / 11 * 10)
            ) < 100)
                answer.push_back(7);
            else
                answer.push_back(0);
        //Segement in top right
        } else if (recog.at<uchar>(
            cv::Point2f(box.x + box.width / 11 * 10, box.y + box.height / 4)
        ) < 100) {
            //5 or 6
            if (recog.at<uchar>(
                cv::Point2f(box.x + box.width / 11, box.y + box.height / 4 * 3)
            ) < 100)
                answer.push_back(5);
            else
                answer.push_back(6);
        //Segment in top left
        } else if (recog.at<uchar>(
            cv::Point2f(box.x + box.width / 11, box.y + box.height / 4)
        ) < 100) {
            //2 or 3
            if (recog.at<uchar>(
                cv::Point2f(box.x + box.width / 11, box.y + box.height / 4 * 3)
            ) < 100)
                answer.push_back(3);
            else
                answer.push_back(2);
        //Segment in top center
        } else if (recog.at<uchar>(
            cv::Point2f(box.x + box.width / 2, box.y + box.height / 11)
        ) < 100)
            answer.push_back(4);
        //8 or 9
        else if (recog.at<uchar>(
            cv::Point2f(box.x + box.width / 11, box.y + box.height / 4 * 3)
        ) < 100)
            answer.push_back(9);
        else
            answer.push_back(8);
    }

    std::cout << "Answer: ";
    for (auto digit: answer)
        std::cout << digit;
    std::cout << std::endl;

    cv::waitKey(0);
}

SSD0::SSD0(char* pImg) {
    oImg = cv::imread(pImg, cv::IMREAD_COLOR);
}

void SSD0::histAnalysis(cv::Mat& img) {
    int histSize{256};
    float range[]{0, 256};
    const float* histRange{range};
    cv::Mat histogram;

    cv::calcHist(&img, 1, 0, cv::noArray(), histogram, 1, &histSize, &histRange);
    cv::minMaxIdx(histogram, NULL, NULL, NULL, &histMax);

    if (histMax > 200)
        imgType = overexpose;
    else
        imgType = normal;
}

cv::RotatedRect SSD0::extract() {
    cv::Mat channelBGR[3];
    cv::split(oImg, channelBGR);
    histAnalysis(channelBGR[2]);
    cv::Mat kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4))};
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> outlines;
    cv::RotatedRect bounding;
    cv::Point2f verticies[4];

    if (imgType == normal) {
        std::cout << "[info] No lighting interference." << std::endl;
        cv::threshold(channelBGR[2], eImg, 0, 255, cv::THRESH_OTSU);
        cv::morphologyEx(eImg, eImg, cv::MORPH_ERODE, kernel);

        

        bounding = cv::RotatedRect{cv::Point2f(30, 30), cv::Point2f(490, 30), cv::Point2f(490, 190)};
    } else {
        std::cout << "[info] Lighting interfered." << std::endl;
        cv::Mat BxG{};
        cv::addWeighted(channelBGR[0], 0.28, channelBGR[1], 0.28, 0, BxG);
        cv::subtract(channelBGR[2], BxG, eImg);
        cv::threshold(eImg, eImg, 114, 255, cv::THRESH_BINARY);
        cv::morphologyEx(eImg, eImg, cv::MORPH_ERODE, kernel);
        cv::morphologyEx(eImg, eImg, cv::MORPH_DILATE, kernel);

        cv::findContours(eImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        for (auto cont: contours) {
            for (auto point: cont)
                outlines.push_back(point);
        }
        bounding = cv::minAreaRect(outlines);
        if (bounding.size.height > bounding.size.width) {
            bounding.angle += 90;
            float temp = bounding.size.height;
            bounding.size.height = bounding.size.width;
            bounding.size.width = temp;
        }
        bounding.points(verticies);
        if (bounding.size.width / bounding.size.height < 2.5) {
            verticies[2].x += 120 * cosf(bounding.angle / 90 * M_PI);
            verticies[2].y += 120 * sinf(bounding.angle / 90 * M_PI);
            outlines.push_back(verticies[2]);
            bounding = cv::minAreaRect(outlines);
            bounding.angle += 90;
            float temp = bounding.size.height;
            bounding.size.height = bounding.size.width;
            bounding.size.width = temp;
        }
    }
    bounding.points(verticies);
    cv::Point2f dst[4] {cv::Point2f(0, 160), cv::Point2f(0, 0),
                       cv::Point2f(460, 0), cv::Point2f(460, 160)};

    transform = cv::getAffineTransform(verticies, dst);

    return bounding;
}