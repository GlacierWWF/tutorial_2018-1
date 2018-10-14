/*****************************************
 *  @file    digit4_recognize.cpp
 *  @brief   functions to recogiize digits
 *
 *----------------------------------------
 *  Details:
 *----------------------------------------
 *  @author  HausinLynn
 *  @email   linhx36@mail2.sysu.edu.cn
 *  @version 1.0.0.1
 *  @date    10/12/2018
 *----------------------------------------
 *
 *----------------------------------------
 *  Change History:
 *  <date>     | <version> | <author>
 *----------------------------------------
 *  10/12/2018 | 1.0.0.1   | HausinLynn
 *----------------------------------------
 *
 ****************************************/

#include <cmath>
#include "digit4_recognize.hpp"

/**
 * @brief    create a new window to show image
 *
 * @param    win_name   --   name of window
 * @param    img        --   image to be shown
 */
void digit4::new_window(string win_name, Mat img) {
	namedWindow(win_name, WINDOW_AUTOSIZE);
	imshow(win_name, img);
}

/**
 * @brief	 binarize image
 *
 * @param    img     --   image to be binarized
 * @param    Rthresh --   threshold of red channel
 * @param    Gthresh --   threshold of green channel
 * @param    Bthresh --   threshold of blue channel
 */
void digit4::binarize(Mat& img, int Rthresh, int Gthresh, int Bthresh) {
	/* split */
	vector<Mat> channels;
	split(img, channels);

	Mat 
		blue_channel = channels[0],    /*!< blue channel */
		green_channel = channels[1],   /*!< green channel */
		red_channel = channels[2];	   /*!< red channel */

	Mat 
		blue_channel_bin,    /*!< binary of blue channel */
		green_channel_bin,	 /*!< binary of green channel */
		red_channel_bin;	 /*!< binary of red channel */

	/* binarize */
	threshold(blue_channel, blue_channel_bin, Bthresh, 255, THRESH_BINARY_INV);
	threshold(green_channel, green_channel_bin, Gthresh, 255, THRESH_BINARY_INV);
	threshold(red_channel, red_channel_bin, Rthresh, 255, THRESH_BINARY);

	Mat bin_img = blue_channel_bin & green_channel_bin & red_channel_bin;
	img = bin_img.clone();    
}

/**
 * @brief	 process the image with Gaussian filter
 *
 * @param    img   --   image to be processed
 * @param    ksize --   kernel size
 */
void digit4::gaussian_blur(Mat& img, Size ksize) {
	Mat blur_img;	/*!< filtered image */
	
	double sigmaX = 0.0;
	double sigmaY = 0.0;
	GaussianBlur(img, blur_img, ksize, sigmaX, sigmaY);
	
	img = blur_img.clone();
}

/**
 * @brief	 dilate image
 *
 * @param    img   --   image to be dilated
 * @param    ksize --   kernel size
 */
void digit4::dilate(Mat& img, Size ksize) {
	Mat dil_img;	/*!< dilated image */
	Mat element;	/*!< structuring */

	element = getStructuringElement(MORPH_RECT, ksize);
	dilate(img, dil_img, element);

	img = dil_img.clone();
}

/**
 * @brief	 erode image
 *
 * @param    img   --   image to be eroded
 * @param    ksize --   kernel size
 */
void digit4::erode(Mat& img, Size ksize) {
	Mat ero_img;	/*!< eroded image */
	Mat element;	/*!< structuring */

	element = getStructuringElement(MORPH_RECT, ksize);
	erode(img, ero_img, element);
	
	img = ero_img.clone();
}

/**
 * @brief	 close operation
 *
 * @param    img   --   image to be processed
 * @param    ksize --   kernel size
 */
void digit4::close(Mat& img, Size ksize) {
	Mat clo_img;	/*!< close iamge */
	Mat element;	/*!< structuring */

	element = getStructuringElement(MORPH_RECT, ksize);
	morphologyEx(img, clo_img, MORPH_CLOSE, element);

	img = clo_img.clone();
}

/**
 * @brief	 blur the edge of image
 *
 * @param    img   --   image to be processed
 */
void digit4::blur_edge(Mat& img) {
	dilate(img, Size(12, 12));
	
	Size img_size = img.size();     /*!< size of image */
	int height = img_size.height;	/*!< height of image */
	int width = img_size.width;		/*!< width of image */
	
	/* fill the edge with flood */
	for(int i = 0; i < height; i++) {
		floodFill(img, Point(0, i), Scalar(0));
		floodFill(img, Point(width - 1, i), Scalar(0));
	}
	for(int j = 0; j < width; j++) {
		floodFill(img, Point(j, 0), Scalar(0));
		floodFill(img, Point(j, height - 1), Scalar(0));
	}

	erode(img, Size(12, 12));
}

/**
 * @brief	 adjust the angle of image
 *
 * @param    img   --   image to be processed
 */
void digit4::adjust(Mat& img) {
	/* preprocess */
	Mat original_img = img.clone();
	gaussian_blur(original_img, Size(9, 9));
	binarize(original_img, 150, 150, 150);
	blur_edge(original_img);
	erode(original_img, Size(5, 5));
	dilate(original_img, Size(5, 5));
	
	/* get the external rects of digits */
	vector<Rect> rects;
	catch_digit(original_img, rects);

	/* calculate slope of regression line */
	float x_total = 0.0;
	float y_total = 0.0;
	float x_mean;
	float y_mean;
	for(int i = 0; i < rects.size(); i++) {
		x_total += rects[i].x;
		y_total += rects[i].y;
	}
	x_mean = x_total / (1.0 * rects.size());
	y_mean = y_total / (1.0 * rects.size());
	float num = 0.0;
	float den = 0.0;
	for(int i = 0; i < rects.size(); i++) {
		num += (rects[i].x - x_mean) * (rects[i].y - y_mean);
		den += (rects[i].x - x_mean) * (rects[i].x - x_mean);
	}
	float slope = num / (1.0 * den);	/*!< slope */

	float angle = atan(slope) * 180 / 3.14;    /*!< angle need to rotate */
	if(angle > 5) {
		Point2f center(img.cols/2, img.rows/2);
		Mat rot_mat = getRotationMatrix2D(center, angle, 1);
		Rect box = RotatedRect(center, img.size(), angle).boundingRect();

		rot_mat.at<double>(0, 2) += box.width / 2.0 - center.x;
		rot_mat.at<double>(1, 2) += box.height / 2.0 - center.y;
	
		/* rotate */
		Mat rot_img;
		warpAffine(img, rot_img, rot_mat, box.size());
		img = rot_img.clone();
	}
}

/**
 * @brief	 get the external rect of each digits
 *
 * @param    img   --   image to be processed
 * @param    digit_rects   --   external rects
 */
void digit4::catch_digit(Mat& bin_img, vector<Rect>& digit_rects) {
	/* find contours */
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bin_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	/* get external rect of each contours */
	vector<Rect> rects;
	for(int i = 0; i < contours.size(); i++) {
		/* exchange contour to rect */
		Rect rect = boundingRect(contours[i]);
		if(rect.width < rect.height * 2 / 5) {
			rect.x = rect.x - rect.width * 3 / 2;
			rect.width = rect.width * 5 / 2;
		}

		rects.push_back(rect);
	}
	
	/* bubble sort the rects in order of area */
	for(int i = 0; i < rects.size(); i++) {
		for(int j = 0; j < rects.size() - i -1; j++ ) {
			if(rects[j].area() < rects[j+1].area()) {
				Rect rect = rects[j];
				rects[j] = rects[j+1];
				rects[j+1] = rect;
			}
		}
	}
	
	/* the 4 largest rects is external rects of digits */
	for(int i = 0; i < 4; i++) {
		digit_rects.push_back(rects[i]);
	}
}

/**
 * @brief	 draw external rects of 4 digits on image
 *
 * @param    img   --   image to be processed
 * @param    digit_rects   --   external rects of 4 digits
 */
void digit4::draw_rects(Mat& img, vector<Rect>& digit_rects) {
	for(int i = 0; i < digit_rects.size(); i++) {
		int lineType = 4;
		int shift = 0;
		/* draw rect */
		rectangle(img, digit_rects[i], Scalar(255, 0 ,255), lineType, shift);
	}
}

/**
 * @brief	 rank the rects in order of abscissa
 *
 * @param    digit_rects   --   rects to be ranked
 */
void digit4::sort_rects(vector<Rect>& digit_rects) {
	/* bubble sort */
	for(int i = 0; i < digit_rects.size(); i++) {
		for(int j = 0; j < digit_rects.size() - i - 1; j++) {
			if(digit_rects[j].x > digit_rects[j+1].x) {
				Rect tem_rect(digit_rects[j]);
				digit_rects[j] = digit_rects[j+1];
				digit_rects[j+1] = tem_rect;
			}
		}
	}
}

/**
 * @brief	 recognize the digit by threading
 *
 * @param    digit   --   digit to be recognized
 *
 * @note	 
 * number of segment:
 *
 *            *******0*******
 *           *               *
 *           *               *
 *           5               1
 *           *               *
 *           *				 *
 *            *******6*******
 *           *				 *
 *           *               *
 *           4               2
 *           *               *
 *           *               *
 *            *******3*******
 *
 * digit:
 *		0   --  segment 0, 1, 2, 3, 4, 5 on     --  0111111 = 63  
 *		1	--	segment 1, 2 on                 --  0000110 = 6
 *		2   --  segment 0, 1, 3, 4, 6 on        --  1011011 = 91
 *		3   --  segment 0, 1, 2, 3, 6 on        --  1001111 = 79
 *		4   --  segment 1, 2, 5, 6 on           --  1100110 = 102
 *		5   --  segment 0, 2, 3, 5, 6 on        --  1101101 = 109
 *		6   --  segment 0, 2, 3, 4, 5, 6 on     --  1111101 = 125
 *		7   --  segment 0, 1, 2                 --  0000111 = 7
 *		8   --  segment 0, 1, 2, 3, 4, 5, 6 on  --  1111111 = 127
 *		9   --  segment 0, 1, 2, 3 ,5 ,6        --  1101111 = 111
 */
int digit4::recognize(Mat digit) {
	int rows = digit.rows;    /*!< rows of digit image */
	int cols = digit.cols;    /*!< cols of digti image */
	vector<Vec4i> zones;	  /*!< zones corresponding to each segments */
	zones.push_back(Vec4i(0, rows/3, cols/2, cols/2 + 1));
	zones.push_back(Vec4i(rows/4, rows/4 + 1, cols/2, cols));
	zones.push_back(Vec4i(rows*3/4, rows*3/4 + 1, cols/2, cols));
	zones.push_back(Vec4i(rows*2/3, rows, cols/2, cols/2 + 1));
	zones.push_back(Vec4i(rows*3/4, rows*3/4 + 1, 0, cols/2));
	zones.push_back(Vec4i(rows/4, rows/4 + 1, 0, cols/2));
	zones.push_back(Vec4i(rows/3, rows*2/3, cols/2, cols/2 + 1));
	
	int tube = 0;
	for(int i = 0; i < zones.size(); i++) {
		bool isWhite = false;
		for(int j = zones[i][0]; j < zones[i][1]; j++) {
			for(int k = zones[i][2]; k < zones[i][3]; k++) {
				/* white pixel indicate the segment is on */
				if(digit.at<uchar>(j, k) == 255) {
					isWhite = true;
					break;
				}
			}
			if(isWhite)
				break;
		}
		if(isWhite)
			tube += pow(2, i); 
	}

	switch(tube) {
		case 63 : return 0;    /*  63   --   0 */
		case 6  : return 1;    /*   6   --   1 */  
		case 91 : return 2;    /*  91   --   2 */
		case 79 : return 3;    /*  79   --   3 */
		case 102: return 4;    /* 102   --   4 */
		case 109: return 5;    /* 109   --   5 */
		case 125: return 6;    /* 125   --   6 */
		case 7  : return 7;    /*   7   --   7 */
		case 127: return 8;    /* 127   --   8 */
		case 111: return 9;    /* 111   --   9 */
	}
}
