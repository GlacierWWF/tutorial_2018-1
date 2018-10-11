#include "head.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: ./test <image_path>" << std::endl;
        std::cout << "Argument number: " << argc << std::endl;
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR);

    if (!image.data) {
        std::cout << "No image data." << std::endl;
        return -1;
    }

    cv::namedWindow("Display image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display image", image);

    cv::waitKey(0);

    return 0;
}