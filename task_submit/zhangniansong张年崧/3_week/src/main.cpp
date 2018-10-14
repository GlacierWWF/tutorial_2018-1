#include <opencv2/opencv.hpp> 
#include <opencv2/ml.hpp>
#include "lineidentify.hpp"
#include "ImageRecify.hpp"
#include "preprocess.hpp"

using namespace std;
using namespace cv;
using namespace cv::ml;

#define TRAINPATH     "./train"
#define TRAINDATANUM  10
#define NORMWIDTH     40
#define NORMHEIGHT    60

bool cmp(const Rect& a, const Rect& b);

int main(int argc, char *argv[])
{

	Mat image_org, image_gry;

	/************parameters****************/
	int _threshold;                   // 0~255, binarize threshold
	int dil;                          // dilation kernel size
	int _blur;                        // Gaussian blur kernel size *must be odd*
	bool ifGamma = 0;				  // flag: if I need gamma correction
	bool isRecify = 0;                // flag: if image is recified
	int w1_low = 10, w1_high = 40;    // width boundary for number "1"
	int w2_low = 55, w2_high = 100;   // width boundary for other numbers
	int h_low = 100, h_high = 160;
	/*************************************/

	if (argc-1 == 2){
		hard(argv[1], argv[2], image_gry, ifGamma, isRecify); 
		if (ifGamma == true) _threshold = 10; else _threshold = 200;
		if (ifGamma == true) dil = 10; else dil = 15;
		_blur = 7;
		w1_low = 10, w1_high = 40;
		w2_low = 75; w2_high = 110;
		h_low = 90;  h_high = 160;
	}
	else if (argc-1 == 1){
		image_org = imread(argv[1]);
		imshow("original image", image_org);
		if (image_org.rows == 180 && image_org.cols == 480){
			
			simple(image_org, image_gry, ifGamma);
			_threshold = 120;
			if (ifGamma == true) dil = 11; else dil = 7;
			_blur = 11;
			w2_low = 60; w2_high = 100;
			w1_low = 10; w1_high = 40;
			h_low = 100; h_high = 160;
		}
		else if (image_org.rows == 600 && image_org.cols == 800){
			actual(image_org, image_gry, isRecify);
			_threshold = 200;
			dil = 13;
			_blur = 5;
			w1_low = 10; w1_high = 40;
			w2_low = 54; w2_high = 100;
			h_low = 95; h_high = 160; 
		}
	}else{
		cout << "the picture doesn't seem to be right" << endl;
		return -1;
	}


	// binarize image
	Mat image_bin;
	threshold(image_gry, image_bin, _threshold, 255, THRESH_BINARY);
	//imshow("image_bin", image_bin);

	// dilated binary image
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(dil, dil));
	dilate(image_bin, image_dil, element);
	imshow("image_dil1", image_dil);

	// edge detection dilated image
	Mat blurred;
	GaussianBlur(image_dil, blurred, Size(_blur,_blur), 0);
	Mat edged;
	Canny(blurred, edged, 50, 200);
	imshow("edged", edged);

	// find all contours and draw them out
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edged, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE); 
	Mat image_copy;
	Scalar color(0,255,0);
	if (isRecify || argc-1==2){
		image_copy = image_gry.clone();
		cvtColor(image_copy, image_copy, cv::COLOR_GRAY2BGR);
	}else{
		image_copy = image_org.clone();
	}
	drawContours(image_copy, contours, -1, color, LINE_8, 8, hierarchy);  
	//imshow("location", image_copy);

	// create and sort bounding boxes
	const size_t size = contours.size();
	vector<Rect> num_location;
	vector<Rect> all_boxes;
	for (int i = 0; i < contours.size(); i++)
	{
		Rect box = boundingRect(Mat(contours[i]));
		int width = box.width;
		int height = box.height;
		all_boxes.push_back(box);
		// output all boxes width & height
		//cout << "box = " << i << " width = " << width << " height = " << height << endl;
		// select boxes
		if ((width >= w1_low && width <= w1_high || width == 70 ||
			width  >= w2_low && width <= w2_high) && 
			height >= h_low  && height <= h_high){

			num_location.push_back(box);
		}
	}
	sort(num_location.begin(), num_location.end(), cmp);
	// remove duplicate boxes
	for (int i = num_location.size(); i > 0; --i){
		if (num_location[i].width == num_location[i-1].width && num_location[i].height == num_location[i-1].height){
			num_location.erase(num_location.begin()+i);
		}
	}

	//Display all bounding boxes
	Mat image_copy2;
	if (isRecify || argc-1==2){
		image_copy2 = image_gry.clone();
		cvtColor(image_copy2, image_copy2, cv::COLOR_GRAY2BGR);
	}else{
		image_copy2 = image_org.clone();
	}
	for (int i=0; i < all_boxes.size(); i++){
		rectangle(image_copy2, all_boxes[i], color, 8, 8, 0);
	}
	//imshow("all bounding boxes", image_copy2);

	// Display selected bounding boxes
	Mat image_copy3;
	if (isRecify || argc-1==2){
		image_copy3 = image_gry.clone();
		cvtColor(image_copy3, image_copy3, cv::COLOR_GRAY2BGR);
	}else{
		image_copy3 = image_org.clone();
	}
	for (int i=0; i < num_location.size(); i++){
		rectangle(image_copy3, num_location[i], color, 8, 8, 0);
		//cout << "selected box = "<< i << " width = " << num_location[i].width << " height = " << num_location[i].height << endl;
	}
	imshow("Number bounding boxes", image_copy3);



	// number extraction with selected bounding boxes
	char filenamew[255];
	int tube_num = 0;
	vector<Mat> tube;
	for (int i = 0; i < num_location.size(); i++)
	{
		if (!IsAllWhite(image_dil(num_location.at(i))))
		{
			tube.push_back(image_dil(num_location.at(i)));
			sprintf(filenamew, "%s%d.jpg", "./location/location", tube_num);
			//imshow(filenamew, tube.at(tube_num));
			imwrite(filenamew, tube.at(tube_num));
			tube_num++;
		}
	}
	
	/*************************------------------------------------********************/
	/*----------------------------------KNN------------------------------------------*/
	/*************************------------------------------------********************/
	char trainfile[100];
	Mat traindata, trainlabel, tmp;
	for (int i = 0; i < TRAINDATANUM; i++)
	{
		sprintf(trainfile, "%s/%d.jpg", TRAINPATH, i);
		tmp = imread(trainfile, IMREAD_GRAYSCALE);
		if (tmp.empty()){
			cout << "training image load failed: " << trainfile << endl;
			return -1;
		}
		threshold(tmp, tmp, 50, 255, THRESH_BINARY);
		resize(tmp, tmp, Size(NORMWIDTH, NORMHEIGHT));
		traindata.push_back(tmp.reshape(0, 1));
		trainlabel.push_back(i);
	}
	traindata.convertTo(traindata, CV_32F);


	int K = 1;
	Ptr<TrainData> tData = TrainData::create(traindata, ROW_SAMPLE, trainlabel);
	Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	knn->train(tData);
	for (int i = 0; i < tube_num; i++)
	{
		resize(tube.at(i), tube.at(i), Size(NORMWIDTH, NORMHEIGHT));
		tube.at(i) = tube.at(i).reshape(0, 1);
		tube.at(i).convertTo(tube.at(i), CV_32F);
		int r = knn->predict(tube.at(i));  
		cout << r ;
	}
	cout << endl;

	waitKey(0);

	return 0;
}

bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}