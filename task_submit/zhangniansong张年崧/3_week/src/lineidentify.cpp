#include "lineidentify.hpp"

bool IsAllWhite(Mat inputmat)
{
	IplImage temp = inputmat;
	if (inputmat.rows * inputmat.cols == cvCountNonZero(&temp))
		return true;
	else
		return false;
}

bool IsAllBlack(Mat inputmat)
{
	IplImage temp = inputmat;
	if (cvCountNonZero(&temp) == 0)
		return true;
	else
		return false;
}

bool Iswhite(Mat inputmat, int row_start, int row_end, int col_start, int col_end)
{
	int white_num = 0;
	for (int i = row_start; i <= row_end; i++)
	{
		for (int j = col_start; j <= col_end; j++)
		{
			if (inputmat.at<uchar>(i, j) == 255)
				white_num++;
		}
	}
	if (white_num > 5)
		return true;
	else
		return false;
}