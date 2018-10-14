#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

Mat src, src_gray, src_bin, src_dil, src_HSV;
Mat dst, detected_edges;
Mat element;

const char* window_name = "Output";
int lowThreshold = 0;
const int ratio = 3;
const int kernel_size =3;

bool cmp(const Rect& a, const Rect& b)
{
	if(a.x<b.x)
		return true;
	else
                return false;
}

bool empty(Mat input, int row_begin, int row_end, int col_begin, int col_end)
{
	int white_num = 0;
	for(int i = row_begin; i <= row_end; i++)
	{
		for(int j = col_begin; j <= col_end; j++)
		{
			if(input.at<uchar>(i,j) ==255)
				white_num++;
		}
	}
	if(white_num >5)
		return true;
	else
		return false;
}

int digtest(Mat input)
{
	int tube;
	int tube_test[7][4]=
	{
		{input.rows*0/3, input.rows*1/3, input.cols*1/2,input.cols*1/2},
		{input.rows*1/3, input.rows*1/3, input.cols*1/2,input.cols},
		{input.rows*2/3, input.rows*2/3, input.cols*1/2,input.cols},
		{input.rows*2/3, input.rows-1, input.cols*1/2,input.cols*1/2},
		{input.rows*2/3, input.rows*2/3, input.cols*0/2,input.cols*1/3},
		{input.rows*1/3, input.rows*1/3, input.cols*0/2,input.cols*1/3},
		{input.rows*0/3, input.rows*2/3, input.cols*1/2,input.cols*1/2},
	};
	if(input.rows/input.cols >2)
	{
		tube = 6;
	}
	else
	{
		for(int i =0; i <7; i++)
		{
			if(empty(input, tube_test[i][0], tube_test[i][1], tube_test[i][2], tube_test[i][3]))
				tube = tube + (int)pow(2, i);
		}
	}

	/*switch(tube)
	{
		case 63:  return 0; break;
		case 6:   return 1; break;
		case 91:  return 2; break;
		case 79:  return 3; break;
		case 102: return 4; break;
		case 109: return 5; break;
		case 125: return 6; break;
		case 7:   return 7; break;
		case 127: return 8; break;
		case 111: return 9; break;

		default: return -1;
	}*/
	return tube;
}

int main(int argc, char** argv)
{
        CommandLineParser parser( argc, argv, "{@input | ./sim_samples/sim_sample1.jpg | input image}" );
        src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
        if( src.empty() )
        {
                std::cout << "no input" << std::endl;
                return -1;
        }
        dst.create( src.size(), src.type() );
        int ind = 0;
        namedWindow (window_name, WINDOW_AUTOSIZE );
	cvtColor( src, src_HSV, COLOR_BGR2HSV );
	inRange(src_HSV, Scalar(0,134,157), Scalar(180,255,255), src_gray);
	threshold(src_gray, src_bin, 50, 255, THRESH_BINARY);
	element = getStructuringElement(MORPH_RECT, Size(15,15));
	dilate(src_bin, src_dil, element);
	blur( src_dil, detected_edges, Size(3,3) );
        imshow("Bin", src_dil);
	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	dst = Scalar::all(0);
        src.copyTo( dst,detected_edges);
	imshow(window_name, dst);
        
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(detected_edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	const size_t size = contours.size();
	vector<Rect> num_location;
	int i;
	/*for(i=0; i<20; i++)
	{
		int j = hierarchy[i][0];
		cout << j << endl;
	}*/
	for(i = 0; i<contours.size(); i++)
	//i=0;
	//while(i == 3)
	{
		num_location.push_back(boundingRect(Mat(contours[i])));
		//num_location.push_back(boundingRect(Mat(contours[8])));
		//num_location.push_back(boundingRect(Mat(contours[12])));
		//int next = hierarchy[i][0];
		//i++;
	}
	//cout << "i=" << num_location.size() << endl;
	sort(num_location.begin(), num_location.end(), cmp);
	vector<Rect> tube;
	int tube_num=0;
	for(int i1 = 0; i1<num_location.size();)
	{
		Mat img = Mat(src_dil, num_location.at(i1));
		Mat imo_copy = img.clone();
		//cout << digtest(imo_copy); 
		imshow("test", imo_copy);
		i1 = i1+2;
		//cout << i1 << endl;
		waitKey(0);
	}

	/*for(int i = 0; i<contours.size(); i++)
	{
		//if(!IsAllWhite(src_dil(num_location.at(i))))
		//{
			tube.push_back(src_dil(num_location.at(i)));
			imshow("test", tube.at(tube_num));
			tube_num++;
		//}
	}*/

	//dst = Scalar::all(0);
        //src.copyTo( dst,detected_edges);
        //imshow(window_name, detected_edges);
	//imshow(window_name, dst);
        waitKey(0);
        return 0;
}

