//Standard I/O
#include <iostream>
//OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class SSD {
        std::string originalImageWindowName {
            "Original image"
        };
        // std::string originalImageUri{};
        void display(cv::Mat&);
        void save(cv::Mat&);
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

class SSD2 {
    SSD* img1;
    SSD* img2;
    cv::Size combinedSize{};
    cv::Mat combined{};

    public:
        SSD2(char*, char*);
        void combine();
        void readDigit();
};