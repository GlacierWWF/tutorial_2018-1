#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;

Mat src, src_gray, src_bin, src_HSV;
Mat dst, detected_edges;
Mat kernel;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size =3;
int kernel_size1 =3;
const char* window_name = "Output";
const int max_value_H = 360/2;
const int max_value = 255;
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
Point anchor;
double delta;
int ddepth;
int erosion_elem = 0;
int erosion_size = 0;
const int max_elem = 2;
const int max_kernel_size = 21;

static void on_low_H_thresh_trackbar(int, void* ) //lh
{
	low_H = min(high_H-1, low_H);
	setTrackbarPos( "Low H", window_name, low_H );
}
static void on_high_H_thresh_trackbar(int, void* ) //hh
{
	high_H = max(high_H, low_H+1);
	setTrackbarPos( "High H", window_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void* ) //ls
{
	low_S = min(high_S-1, low_S);
	setTrackbarPos( "Low S", window_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void* ) //hs	
{
	high_S = max(high_S, low_S+1);
	setTrackbarPos( "High S", window_name, high_S);
}

static void on_low_V_thresh_trackbar(int, void* ) //lv
{
	low_V = min(high_V-1, low_V);
	setTrackbarPos( "Low V", window_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void* ) //hv
{
	high_V = max(high_V, low_V+1);
	setTrackbarPos( "High V", window_name, high_V);
}
/*static void on_kernel_size(int, void* )
{
	kernel = Mat::ones( kernel_size1, kernel_size1, CV_32F)/ (float)(kernel_size1*kernel_size1);
	filter2D(src, src_gray_p, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
	setTrackbarPos( "Kernel Size", window_name, kernel_size1);
}

static void Erosion( int, void* )
{
	int erosion_type = 0;
	if(erosion_elem == 0)
	{
		erosion_type = MORPH_RECT;
	}
	else if(erosion_elem == 1)
	{
		erosion_type = MORPH_CROSS;
	}
	else if(erosion_elem ==2)
	{
		erosion_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement( erosion_type, Size(2*erosion_size+1, 2*erosion_size+1), Point(erosion_size, erosion_size ));
	erode(src, src_gray_p, element);
	setTrackbarPos( "Element:", window_name, erosion_elem);
	setTrackbarPos( "Kernel size:", window_name, erosion_size);
}*/

static void CannyThreshold(int, void*)
{
	blur( src_bin, detected_edges, Size(3,3) );
	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	dst = Scalar::all(0);
	src.copyTo( dst,detected_edges);
	setTrackbarPos( "Min Threshold:", window_name, lowThreshold);
	//imshow( window_name, dst );
}

int main( int argc, char** argv )
{
	CommandLineParser parser( argc, argv, "{@input | ./sim_samples/sim_sample1.jpg | input image}" );
	src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
	if( src.empty() )
	{
		std::cout << "no input" << std::endl;
		return -1;
	}
	dst.create( src.size(), src.type() );
	anchor = Point(-1, -1);
	delta = 0;
	ddepth = -1;
	int ind = 0;
	namedWindow (window_name, WINDOW_AUTOSIZE );
	//createTrackbar( "Element:", window_name, &erosion_elem, max_elem, Erosion);
	//createTrackbar( "Kernel size:", window_name, &erosion_size, max_kernel_size, Erosion);
	//Erosion(0,0);
	//createTrackbar( "Kernel Size", window_name, &kernel_size1, 11, on_kernel_size);
	//on_kernel_size(0,0);
	cvtColor( src, src_HSV, COLOR_BGR2HSV );
	createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
	createTrackbar( "Low H", window_name, &low_H, max_value_H, on_low_H_thresh_trackbar );
	createTrackbar( "High H", window_name, &high_H, max_value_H, on_high_H_thresh_trackbar );
	createTrackbar( "Low S", window_name, &low_S, max_value, on_low_S_thresh_trackbar );
	createTrackbar( "High S", window_name, &high_S, max_value, on_high_S_thresh_trackbar );
	createTrackbar( "Low V", window_name, &low_V, max_value, on_low_V_thresh_trackbar );
	createTrackbar( "High V", window_name, &high_V, max_value, on_high_V_thresh_trackbar );
	while(true)
	{
	inRange(src_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_gray);
	//imshow("test", src_HSV);
	//imshow(window_name, src_gray_p);
	//cvtColor( src_gray_p, src_gray, COLOR_BGR2GRAY);
	//imshow(window_name, dst);
	threshold(src_gray, src_bin, 50, 255, THRESH_BINARY);
	CannyThreshold(0, 0);
	//while(true)
	//{
		imshow("test", src_gray);
		imshow(window_name, dst);
		waitKey(0);
	}
	return 0;
}
	
