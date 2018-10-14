/**************************************
 *  digits recognition project header
 *  @file    digit4_recognize.hpp
 *
 *-------------------------------------
 *  Details:
 *-------------------------------------
 *  @author  HausinLynn
 *  @email   linhx36@mail2.sysu.edu.cn
 *  @version 1.0.0.1
 *  @date    10/12/2018
 *-------------------------------------
 *
 *-------------------------------------
 *  Change History:
 *  <date>     | <version> | <author>
 *-------------------------------------
 *  10/12/2018 | 1.0.0.1   | HausinLynn
 *-------------------------------------
 *
 *************************************/

#ifndef DIGIT4_RECOGNIZE_H
#define DIGIT4_RECOGNIZE_H

/// Headers
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define unsigned char uchar;

using namespace std;
using namespace cv;

/**
 * digits recognition in-use functions
 */
namespace digit4 {
	/**
	 * @brief    create a new window to show image
	 *
	 * @param    win_name   --   name of window
	 * @param    img        --   image to be shown 
	 */
	void new_window(string win_name, Mat img);
	
	/**
	 * @brief    binarize image
	 *
	 * @param    img     --   image to be binarized
	 * @param    Rthresh --   threshold of red channel
	 * @param    Gthresh --   threshold of green channel
	 * @param    Bthresh --   threshold of blue channel
	 */
	void binarize(Mat& img, int Rthresh, int Gthresh, int Bthresh);

	/**
	 * @brief	 process the image with Gaussian filter
	 *
	 * @param    img   --   image to be processed
	 * @param    ksize --   kernel size
	 */
	void gaussian_blur(Mat& img, Size ksize);
	
	/**
	 * @brief    dilate image
	 *
	 * @param	 img   --   image to be dilated
	 * @param    ksize --   kernel size   
	 */
	void dilate(Mat& img, Size ksize);
	
	/**
	 * @brief	 erode image
	 *
	 * @param    img   --   image to be eroded
	 * @param    ksize --   kernel size
	 */
	void erode(Mat& img, Size ksize);
	
	/**
	 * @brief	 close operation
	 *
	 * @param    img   --   image to be processed
	 * @param    ksize --   kernel size
	 */
	void close(Mat& img, Size ksize);
	
	/**
	 * @brief	 blur the edge of image
	 *
	 * @param    img   --   image to be processed
	 */
	void blur_edge(Mat& img);
	
	/**@brief    adjust the angle of image
	 *
	 * @param    img   --   image to be processed
	 */
	void adjust(Mat& img);
	
	/**
	 * @brief	 get the external rect of each digits
	 *
	 * @param    img   --   image to be processed
	 * @param    digit_rects   --   external rects
	 */
	void catch_digit(Mat& bin_img, vector<Rect>& digit_rects);
	
	/**
	 * @brief    draw external rects of 4 digits on image
	 *
	 * @param    img   --   image to be processed
	 * @param    digit_rects   --   external rects of 4 digits
	 */
	void draw_rects(Mat& img, vector<Rect>& digit_rects);
	
	/**
	 * @brief	 rank the rects in order of abscissa
	 *
	 * @param    digit_rects   --   rects to be ranked
	 */
	void sort_rects(vector<Rect>& digit_rects);
	
	/**
	 * @brief	 recognize the digit
	 *
	 * @param    digit   --   digti to be recognized
	 */
	int recognize(Mat digit);
}

#endif
