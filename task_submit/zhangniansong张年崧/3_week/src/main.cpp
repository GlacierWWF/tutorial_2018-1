#include <opencv2/opencv.hpp> 
#include <opencv2/ml.hpp>
#include "lineidentify.hpp"
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
	// handle input images
	Mat image_gry, image_org, image_copy;
	if (argc-1 == 1){
		image_org = imread(argv[1]);
		image_copy = image_org.clone();
		image_gry = imread(argv[1], IMREAD_GRAYSCALE);
		if (image_gry.empty()){
			cout << "open image " << argv[1] << " failed." <<endl;
			return -1;
		}

	}else if (argc-1 == 2){
		// combine two images into 1
		Mat src1 = imread(argv[1], IMREAD_GRAYSCALE);
		Mat src2 = imread(argv[2], IMREAD_GRAYSCALE);
		Mat src1_org = imread(argv[1]);
		Mat src2_org = imread(argv[2]);

		if( !src1.data) {printf("Error loading src1. \n"); return -1;}
		if( !src2.data) {printf("Error loading src2. \n"); return -1;}

		addWeighted(src1, 0.5, src2, 0.5, 0.0, image_gry);
		addWeighted(src1_org, 0.5, src2_org, 0.5, 0.0, image_org);
		image_copy = image_org.clone();

	}else if (argc-1 > 2){
		cout << "too many arguments" << endl;
		return -1;
	} 
	
	// display test image in gray scale 	
	imshow("image_gry", image_gry);
	waitKey(0);
	
	// eliminate blooming
	/*uchar value;
	for (int col = 0; col < test.cols; col++){
		for (int row = 0; row < test.rows; row++){
			value = image_gry.at<unsigned char>(row, col);
			if (value >= 150){
				value *= value - 50;
				image_gry.at<unsigned char>(row, col) = value;
			}
		}
	}
	imshow("elimate blooming", image_gry);
	waitKey(0);*/
	Mat equ;
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(1);
	clahe->apply(image_gry, equ);
	imshow("equalized", equ);
	waitKey(0);

	// make a mask to remove reflection
	Mat mask;
	threshold(image_gry, mask, 150, 255, THRESH_BINARY);
	



	// binarize image
	Mat image_bin;
	threshold(image_gry, image_bin, 150, 255, THRESH_BINARY);
	imshow("image_bin", image_bin);
	waitKey(0);

	// dilated binary image
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
	dilate(image_bin, image_dil, element);
	imshow("image_dil1", image_dil);
	waitKey(0);

	// edge detection dilated image
	Mat blurred;
	GaussianBlur(image_dil, blurred, Size(5,5), 0);
	Mat edged;
	Canny(blurred, edged, 50, 200);
	imshow("edged", edged);
	waitKey(0);

	// find all contours and draw them out
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edged, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE); 
	Scalar color(0, 255, 0);
	drawContours(image_copy, contours, -1, color, LINE_8, 8, hierarchy);  
	imshow("location", image_copy);
	waitKey(0);


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
		cout << "box = " << i << " width = " << width << " height = " << height << endl;
		// select boxes
		if ((width >=70 && width <=100 || width>=25 && width <= 35) && height >= 110 && height <= 150){
			num_location.push_back(box);
		}
	}
	sort(num_location.begin(), num_location.end(), cmp);
	// remove duplicate boxes
	for (int i = num_location.size(); i > 0; --i){
		if (num_location[i].width == num_location[i-1].width){
			num_location.erase(num_location.begin()+i);
		}
	}

	//Display all bounding boxes
	Mat image_copy3 = image_org.clone();
	for (int i=0; i < all_boxes.size(); i++){
		rectangle(image_copy3, all_boxes[i], color, 8, 8, 0);
	}
	imshow("all bounding boxes", image_copy3);
	waitKey(0);
	
	// Display selected bounding boxes
	Mat image_copy2 = image_org.clone();
	for (int i=0; i < num_location.size(); i++){
		rectangle(image_copy2, num_location[i], color, 8, 8, 0);
		cout << "selected box = "<< i << " width = " << num_location[i].width << " height = " << num_location[i].height << endl;
	}
	imshow("Number bounding boxes", image_copy2);
	waitKey(0);

	// number extraction with selected bounding boxes
	char filenamew[255];
	int tube_num = 0;
	vector<Mat> tube;
	for (int i = 0; i < num_location.size(); i++)
	{
		if (!IsAllWhite(image_dil(num_location.at(i))))
		{
			tube.push_back(image_bin(num_location.at(i)));
			sprintf(filenamew, "%s%d.jpg", "./location/location", tube_num);
			imshow(filenamew, tube.at(tube_num));
			imwrite(filenamew, tube.at(tube_num));
			tube_num++;
		}
	}
	
	// number extraction with all bounding boxes
	/*char filenamew[255];
	int tube_num = 0;
	vector<Mat> tube;
	for (int i = 0; i < all_boxes.size(); i++)
	{
		if (!IsAllWhite(image_dil(all_boxes.at(i))))
		{
			tube.push_back(image_bin(all_boxes.at(i)));
			sprintf(filenamew, "%s%d.jpg", "./location/location", tube_num);
			imshow(filenamew, tube.at(tube_num));
			imwrite(filenamew, tube.at(tube_num));
			tube_num++;
		}
	}*/
	
	//cout << "start training" << endl;
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

	waitKey(1);
	//destroyAllWindows();
	return 0;
}

bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}
