#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
		Mat img = imread("sysu.jpeg");
		namedWindow("SYSU");
		imshow("SYSU",img);
		waitKey(4000);
		cout << "Thank you for using.";

		return 0;
}

