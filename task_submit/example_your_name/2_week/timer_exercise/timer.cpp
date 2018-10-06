
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
Mat img =imread("/home/qinxy/opencv-lena/hy/001.jpg");
imshow("image",img);
waitKey();
return 0;
}
