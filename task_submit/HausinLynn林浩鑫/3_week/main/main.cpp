/*****************************************
 *  @file    main.cpp
 *  @brief   program to recogiize digits
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

#include <sstream>
#include <unistd.h>
#include "digit4_recognize.hpp"

/**
 * @brief	main function
 *
 * @param   argc   --   counts of argument
 * @param   argv   --   variables of argument
 *
 * @return  integer
 */
int main (int argc, char** argv) {
	/* read image */
	cout << "reading .............................. ";
	Mat img = imread(argv[1], -1);
	digit4::new_window("source", img);
	cout << "done." << endl;
	
	/* adjust the angle */
	cout << "adjusting ............................ ";
	digit4::adjust(img);
	digit4::new_window("adjusted", img);
	Mat original_img = img.clone();
	cout << "done." << endl;
	
	/* preprocess */
	cout << "gaussian bluring ..................... ";
	digit4::gaussian_blur(img, Size(9, 9));    
	cout << "done." << endl;
	cout << "binarizing ........................... ";
	digit4::binarize(img, 150, 175, 175);	   
	cout << "done." << endl;
	cout << "bluring edge ......................... ";
	digit4::blur_edge(img);					   
	cout << "done." << endl;
	//cout << "close operating ...................... ";
	//digit4::close(img, Size(15, 15));
	//cout << "done." << endl;
	cout << "eroding .............................. ";
	digit4::erode(img, Size(5, 5));			   
	cout << "done." << endl;
	cout << "dilating ............................. ";
	digit4::dilate(img, Size(5, 5));		   
	cout << "done." << endl;
	digit4::new_window("binary", img);
	
	/* get the external rects of each digits */
	cout << "getting digits........................ ";
	vector<Rect> rects;
	digit4::catch_digit(img, rects);
	digit4::sort_rects(rects);
	
	/* draw external rects of each digits */
	waitKey(500);
	digit4::draw_rects(original_img, rects);
	imshow("adjusted", original_img);
	cout << "done." << endl;

	vector<Mat> digit_imgs;
	stringstream res_stream;
	for(int i = 0; i < rects.size(); i++) {
		/* cut the digits from image */
		Mat digit_img = Mat(img, rects[i]);
		digit_imgs.push_back(digit_img);
		
		stringstream title_stream;
		title_stream << "digit" << i + 1;
		string title = title_stream.str();
		waitKey(500);
		digit4::new_window(title, digit_img);
		
		/* recognize each digits */
		cout << "identifying digit" << i + 1 << " ................... ";
		int digit = digit4::recognize(digit_img);
		res_stream << digit;
		cout << "done." << endl;
		cout << "the digit" << i + 1 << " is: " << digit << endl; 
	}
	string result = res_stream.str();
	
	cout << "recognize done.";
	cout << "result: " << result << endl;
	waitKey(0);
	return 0;
}
