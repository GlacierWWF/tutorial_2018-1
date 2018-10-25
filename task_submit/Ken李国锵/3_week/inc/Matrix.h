#ifndef _MATRIX_H_
#define _MATRIX_H_

#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<fstream>

#define pix_row 64
#define pix_col 32
#define debug

using namespace std;
using namespace cv;

class matrix
{
		public:
				vector<vector<int>>test_matrix;

				matrix();

				void test_read();

				int compare(vector<vector<int>> &, int);
};

#endif

