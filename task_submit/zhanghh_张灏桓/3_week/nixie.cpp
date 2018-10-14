//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_14
//Version:v1.0.0
//Abstract:Read the number from pixel_cube.

#include "nixie.hpp"
using namespace cv;
using namespace std;
using namespace std::chrono;


bool cmp(const Rect& a, const Rect& b)
{ 
  if (a.x < b.x) return true;
  return false;
}

bool White_noise(Mat image_mat)
{
	IplImage image_Ipl = (IplImage)image_mat;
	//cout << "all_pixelall_pixel:" << (float)cvCountNonZero(&temp) / (float)(image_mat.rows * image_mat.cols) <<endl;
	if ((float)cvCountNonZero(&image_Ipl) / (float)(image_mat.rows * image_mat.cols) > 0.95)
		return true;
	return false;
}

//test if it is a LED tube
bool test_LED(Mat image_mat, int row_start, int row_end, int col_start, int col_end)
{
	int white_pixel = 0;
	int all_pixel = (row_end - row_start + 1) * (col_end - col_start + 1);
	if(row_end - row_start < col_end - col_start) //test white pixel of the middle line
	{
		int mid = (col_end + col_start + 1) / 2;
		int mid_cal = 0;
		for(int i = row_start; i <= row_end; i++) {
			if (image_mat.at<uchar>(i, mid))
				mid_cal++;
		}
		if((float)mid_cal / (float)(col_end - col_start + 1) < 0.2 )
			return false;
	}
	else
	{
		int mid = (row_end + row_start + 1) / 2;
		int mid_cal = 0;
		for(int i = col_start; i <= col_end; i++) {
			if (image_mat.at<uchar>(mid, i))
				mid_cal++;
		}
		if((float)mid_cal / (float)(row_end - row_start + 1) < 0.2 )
			return false;
	}

	for (int i = row_start; i <= row_end; i++)
	{
		for (int j = col_start; j <= col_end; j++)
		{
			if (image_mat.at<uchar>(i, j))
				white_pixel++;
		}
	}
//	cout << white_pixel << "   " << all_pixel << endl;
	if ((float)white_pixel / (float)all_pixel > 0.5)
		return true;
	return false;
}

//calculate the proportion of white pixel
float white_proportion(Mat image_mat, int row_start, int row_end, int col_start, int col_end)
{
	int white_pixel = 0;
	int all_pixel = (row_end - row_start + 1) * (col_end - col_start + 1);
	for (int i = row_start; i <= row_end; i++)
	{
		for (int j = col_start; j <= col_end; j++)
		{
			if (image_mat.at<uchar>(i, j))
				white_pixel++;
			//cout << white_pixel << endl;
		}
	}
	
	//cout << all_pixel << " " << white_pixel << " " << (float)white_pixel / (float)all_pixel << endl;	
	return (float)white_pixel / (float)all_pixel;
}

//test if the image is a numebr
int test_numebr(Mat image_mat) 
{
	if(image_mat.rows < 85 || image_mat.cols < 15)
		return -1;
	if(image_mat.rows > 180 || image_mat.cols > 180)
		return -1;
	int number = 0;
	int LED_part[7][4] =
	{
		{ image_mat.rows * 0    , image_mat.rows * 1 / 5, image_mat.cols * 0    , image_mat.cols - 1     }, // a
		{ image_mat.rows * 0    , image_mat.rows * 1 / 2, image_mat.cols * 7 / 10, image_mat.cols - 1    }, // b
		{ image_mat.rows * 1 / 2, image_mat.rows - 1    , image_mat.cols * 6 / 10, image_mat.cols - 1    }, // c
		{ image_mat.rows * 5 / 6, image_mat.rows - 1    , image_mat.cols * 0    , image_mat.cols - 1     }, // d
		{ image_mat.rows * 1 / 2, image_mat.rows - 1    , image_mat.cols * 0    , image_mat.cols * 1 / 3 }, // e
		{ image_mat.rows * 0    , image_mat.rows * 1 / 2, image_mat.cols * 0    , image_mat.cols * 1 / 3 }, // f
		{ image_mat.rows * 2 / 5, image_mat.rows * 3 / 5, image_mat.cols * 1 / 8, image_mat.cols * 6 / 8 }, // g
	};
	int LED_part2[2][4] = 
	{
		{ image_mat.rows * 2 / 3, image_mat.rows - 1    , image_mat.cols * 1 / 2, image_mat.cols * 1 / 2 }, // d2
		{ image_mat.rows * 1 / 3, image_mat.rows * 2 / 3, image_mat.cols * 1 / 2, image_mat.cols * 1 / 2 }, // g2
	};

	if ((float)image_mat.rows / (float)image_mat.cols > 2
		&& white_proportion(image_mat, image_mat.rows * 0, image_mat.rows - 1, image_mat.cols * 0, image_mat.cols - 1) > 0.56)
	{
		number = 6;
	}
	else
	{	
		cout << "Lighting LED: ";
		for (int i = 0; i < 7; i++)
		{
			if (test_LED(image_mat, LED_part[i][0] , LED_part[i][1], LED_part[i][2], LED_part[i][3]))
      			{
				number += (int)pow(2, i);
				cout << "1 ";
			}
			else cout << "0 ";
		}
		cout << endl;
	}

	switch (number)
	{
		case  63: return 0;  break;
		case  31: return 0;  break;
		case   6: return 1;  break;
		case  91: return 2;  break;
		case  79: return 3;  break;
		case 102: return 4;  break;
		case 109: return 5;  break;
		case 125: return 6;  break;
		case   3: return 7;  break;
		case   7: return 7;  break;
		case  39: return 7;  break;
		case 127: return 8;  break;
		case 111: return 9;  break;
		default: return -1;
	}
	
}


