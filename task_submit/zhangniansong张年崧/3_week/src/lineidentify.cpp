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

/************    **********/
bool Iswhite(Mat inputmat, int row_start, int row_end, int col_start, int col_end)
{
	int white_num = 0;
	for (int i = row_start; i <= row_end; i++)
	{
		for (int j = col_start; j <= col_end; j++)
		{
			if (inputmat.at<uchar>(i, j) == 255)
				white_num++;
			//cout << white_num << endl;
		}
	}
	if (white_num > 5)
		return true;
	else
		return false;
}

int TubeIdentification(Mat inputmat) //
{
	int tube = 0;
	int tubo_roi[7][4] =
	{
		{ inputmat.rows * 0 / 3, inputmat.rows * 1 / 3, inputmat.cols * 1 / 2, inputmat.cols * 1 / 2 }, // a
		{ inputmat.rows * 1 / 3, inputmat.rows * 1 / 3, inputmat.cols * 2 / 3, inputmat.cols - 1     }, // b
		{ inputmat.rows * 2 / 3, inputmat.rows * 2 / 3, inputmat.cols * 2 / 3, inputmat.cols - 1     }, // c
		{ inputmat.rows * 2 / 3, inputmat.rows - 1    , inputmat.cols * 1 / 2, inputmat.cols * 1 / 2 }, // d
		{ inputmat.rows * 2 / 3, inputmat.rows * 2 / 3, inputmat.cols * 0 / 3, inputmat.cols * 1 / 3 }, // e
		{ inputmat.rows * 1 / 3, inputmat.rows * 1 / 3, inputmat.cols * 0 / 3, inputmat.cols * 1 / 3 }, // f
		{ inputmat.rows * 1 / 3, inputmat.rows * 2 / 3, inputmat.cols * 1 / 2, inputmat.cols * 1 / 2 }, // g
	};

	if (inputmat.rows / inputmat.cols > 3)   // 1 is special,which is much narrower than others
	{
		tube = 6;
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{

			if (Iswhite(inputmat, tubo_roi[i][0] , tubo_roi[i][1], tubo_roi[i][2], tubo_roi[i][3]))
				tube = tube + (int)pow(2, i);
		}
	}

	switch (tube)
	{
		case  63: return 0;  break;
		case   6: return 1;  break;
		case  91: return 2;  break;
		case  79: return 3;  break;
		case 102: return 4;  break;
		case 109: return 5;  break;
		case 125: return 6;  break;
		case   7: return 7;  break;
		case 127: return 8;  break;
		case 111: return 9;  break;

		default: return -1;
	}
}

//char trainfile[10];
//void TraindataRead(Mat* traindata, int traindatanum)
//{
//	for (int i = 0; i < traindatanum; i++)
//	{
//		sprintf(trainfile, "%d.bmp", i);
//		cout << trainfile << endl;
//		traindata[i] = imread(trainfile, 0);
//		threshold(traindata[i], traindata[i], 50, 255, THRESH_BINARY);
//	}
//
//}
