/* Title: main.cpp
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-11-08
 * Version: 1.0.0
 * Main program to match SIFT feature point of two images 
 */
#include "SiftHelpers.h"

int main(int argc, char **argv)
{
  try {

		if(argc < 2)
		{
			cout << "Insufficent number of arguments; correct usage:" << endl;
			cout << "   ./bin/sift ./img/0.jpg ./img/1.jpg" << endl;
			return -1;
		}	
		Image queryImage(argv[1]);

		vector<Image> images;
		Image I(argv[2]);
		images.push_back(I);

		cout  << "input finish." << endl;

		Image::descriptorMatching1(queryImage,images);	
			
	}catch(const string &err) 
	{
		cerr << "Error: " << err << endl;
	}
}








