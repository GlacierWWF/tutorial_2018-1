#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Process.hpp"
#include "Degree.hpp"

using namespace cv;
using namespace std;

//void hard(char* arg1, char* arg2, Mat& image_gry, bool& ifGamma, bool& isRecify); 
// funtion hard takes in two strings and returns a Mat

void simple(Mat& image_org, Mat& image_gry, bool& ifGamma){
// function simple takes in a Mat and returns a Mat
	vector<Mat> image_bgr;
	split(image_org, image_bgr);
	Mat image_r = image_bgr[2].clone();
	Scalar tempVal = mean(image_r);
	float mean = tempVal.val[0];
	if (mean >= 110){
        	ifGamma = true;
		MyGammaCorrection(image_r, image_gry, 25.0);
    	}
	else{
        image_gry = image_r;
	}
}
void actual(Mat& image_org, Mat& image_gry, bool& isRecify){
	vector<Mat> image_bgr;
   	split(image_org, image_bgr);
    	Mat image_r = image_bgr[2].clone();
    	Mat temp;
    	Mat image_rec;
    	double degree = CalcDegree(image_r, temp);
    	if (degree > 9.0){
        	// Image Reicfy
       		isRecify = true;
        	//cout << "I need image recify!" << endl;
	    	Mat image_temp = image_r.clone();
	    	ImageRecify(image_temp, image_rec);
    	}
	else{
        	image_rec = image_r.clone();
    	}
	// Do I remove the glare?
    	Scalar tempVal = mean(image_r);
    	float mean = tempVal.val[0];
    	if (mean >= 170){
        Mat tmp = image_rec.clone();
        cv::fastNlMeansDenoising(tmp, image_rec, 5.0);
        MyGammaCorrection(image_rec, image_gry, 25.0);
    	}
	else{
        image_gry = image_rec;
	}
}
bool cmp(const Rect&a,const Rect&b)
{
	if(a.x<b.x)
	return 1;
	return 0;
}
void MyGammaCorrection(Mat& src, Mat& dst, float fGamma)
{
	CV_Assert(src.data);

	// accept only char type matrices
	CV_Assert(src.depth() != sizeof(uchar));

	// build look up table
	unsigned char lut[256];
	for( int i = 0; i < 256; i++ )
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f);
	}

	dst = src.clone();
	const int channels = dst.channels();
	switch(channels)
	{
		case 1:
			{

				MatIterator_<uchar> it, end;
				for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )
					*it = lut[(*it)];

				break;
			}
		case 3: 
			{

				MatIterator_<Vec3b> it, end;
				for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )
				{
					//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0; 
					//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0; 		
					//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;
					(*it)[0] = lut[((*it)[0])];
					(*it)[1] = lut[((*it)[1])];
					(*it)[2] = lut[((*it)[2])];
				}

				break;

			}
	}
}

