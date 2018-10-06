#include <jishiqi2.h>

using namespace std;
using namespace cv;

void Photo::Open()

{
       Mat img =imread("/home/qinxy/opencv-lena/hy/001.jpg");
       imshow("image",img);
       waitKey();
       return 0;
       }

void Photo::Quit()

{
       cv::destroyWindow("001.jpg");
       waitkey();
       return 0;
       }
