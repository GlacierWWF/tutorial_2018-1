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
        void readDigit();

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
        cv::Mat warpped{};
        std::vector<int> answer{};

    public:
        SSD(char*);
        void playground();

};