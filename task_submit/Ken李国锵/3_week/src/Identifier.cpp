/******************************
 * **Identifier.cpp
 * Author:Ken李国锵
 * Date:2018/10/12
 * Version:1.0.0
 * Abstract:
 * ***************************/

#include"../inc/Identifier.h"
#include"../inc/Matrix.h"

void BinImg(Mat &temp, int num)
{
		int a;
		if( num == 3 )
				a = 200;
		else
				a = 180;
		threshold(temp, temp, a, 255, CV_THRESH_BINARY);
}

vector<Rect> sort_rec(vector<vector<Point>> &contours)
{
		int i, j;
		vector<Rect> temp;
		Rect rec;
		for(i = 0; i < contours.size(); i++)
				temp.push_back(boundingRect(contours[i]));
		for(i = 0; i < temp.size() - 1; i++)
				for(j = 0; j < temp.size() -1; j++)
						if(temp[j].x > temp[j + 1].x)
						{
								rec = temp[j];
								temp[j] = temp[j + 1];
								temp[j + 1] = rec;
						}
		int median = find_median(temp,0);
		for(i = 0; i < temp.size(); i++)
		{
				if(temp[i].width > median + 10)
						temp[i].width = median +10;
		}
		return temp;
}

void VecImg(vector<vector<int>> &temp_value, Mat &fix_imgs, int num)
{
		int i, j;
		for(i = 0; i < fix_imgs.rows; i++)
		{
				uchar *ptr = fix_imgs.ptr<uchar>(i);
				for(j = 0; j < fix_imgs.cols; j++)
				{
						if(int(ptr[j]) != 0)
								temp_value[num][i * fix_imgs.cols + j] = 1;
						else
								temp_value[num][i * fix_imgs.cols + j] = 0;
				}
		}
}

void CleanCon(vector<vector<Point>> &contours)
{
		vector<vector<Point>>::iterator iter = contours.begin();
		double area;
		while(iter != contours.end())
		{
				area = abs(contourArea(*iter));
				if(area <= 1750 || area > 18000 ||
								boundingRect(*iter).height < 90)
						iter = contours.erase(iter);
				else
						iter++;
		}

		int median, i;
		vector<Rect>temp;
		for(i = 0; i < contours.size(); i++)
				temp.push_back(boundingRect(contours[i]));
		median = find_median(temp, 1);
		iter = contours.begin();
		while(iter != contours.end())
		{
				if(boundingRect(*iter).height > median + 20
				|| boundingRect(*iter).height < median - 25)
						iter = contours.erase(iter);
				else
						iter++;
		}
}

void gauss(Mat &a)
{
		GaussianBlur(a, a, Size(3,3), 0);
}

int find_median(const vector<Rect> a, int n)
{
		vector<int> median;
		int i, j;
		if(n == 0)
				for(i = 0; i < a.size(); i++)
						median.push_back(a[i].width);
		else
				for(i = 0; i < a.size(); i++)
						median.push_back(a[i].height);
		for(i = 0; i < median.size() - 1; i++)
				for(j = 0; j < median.size() - 1; j++)
						if(median[j] > median[j + 1])
						{
								int temp = median[j];
								median[j] = median[j + 1];
								median[j + 1] = temp;
						}
		int length = median.size();
		return (length % 2 == 0) ? (median[length / 2 - 1] + median[length / 2]) / 2 : (median[length / 2]);
}
void uniform_size(vector<Mat> &imgs, vector<Mat> &uni_imgs)
{
		int i;
		Size uni_size(pix_col, pix_row);
		cout << endl;
		for(i = 0; i < imgs.size(); i++)
		{
				resize(imgs[i], uni_imgs[i], uni_size);
				cout << "@: uniform picture" << i << endl;
				imshow(to_string(i), uni_imgs[i]);
				waitKey(1000);
		}
}

void prepro(Mat &img)
{
		Mat imgHSV;
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		int i, j;
		for(i = imgHSV.rows / 3; i < imgHSV.rows * 2 / 3; i++)
		{
				uchar *ptr = imgHSV.ptr(i);
				for(j = 0; j <imgHSV.cols; j++)
				{
						int hrange = *(ptr + j * 3);
						int srange = *(ptr + 1 + j * 3);
						int vrange = *(ptr + 2 + j * 3);
						if((hrange >= 10 && hrange <= 165 && srange >= 1 && srange <= 40 && vrange >= 140)
						|| (hrange >= 30 && hrange <= 45 && srange >= 60 && srange <= 120 && vrange >= 150))
						{
								
								*(ptr + j * 3) = 0;
								*(ptr + 1 + j * 3) = 0;
								*(ptr + 2 + j * 3) = 0;
						}
				}
		}
		cvtColor(imgHSV, img, COLOR_HSV2BGR);
		gauss(img);
}

void ifRotate(vector<Mat> & imgs, vector<Rect> & recs)
{
		int i;
		double total_x = 0, total_y = 0;
		int min, max;
		min = recs[0].y;
		max = recs[0].y;
		vector<int> xx;
		vector<int> yy;
		for(i = 0; i < recs.size(); i++)
		{
				total_x += recs[i].x;
				total_y += recs[i].y;
				yy.push_back(recs[i].y);
				if(min > recs[i].y)
						min = recs[i].y;
				if(max < recs[i].y)
						max = recs[i].y;
		}
		if(max - min <= 30)
		{
				cout << "@: no rotate" << endl;
				return ; 
		}
		
		double angle;
		double average_y = total_y / recs.size();
		double average_x = total_x / recs.size();
		double first_x = recs[0].x;
		double first_y = recs[0].y;
		
		angle = atan2(average_y - first_y , average_x - first_x);
		angle = angle * 180  / 3.14;
		if(average_y > first_y)
				angle = abs(angle);
		else if(angle > 0)
				angle *= -1;
		
		Size size;
		Point2f center;
		Mat M;
		Rect rec;

		int length = imgs.size();
		for(i = 0; i < length; i++)
		{
				size = imgs[i].size();
				center.x = imgs[i].cols / 2;
				center.y = imgs[i].rows / 2;
				M = getRotationMatrix2D(center, angle, 1);
				rec = RotatedRect(center, size, angle).boundingRect();
				warpAffine(imgs[i], imgs[i], M, rec.size());
				rec = boundingRect(imgs[i]);
				if(angle > 0)
				{
						rec.width -= 7;
						rec.height -= 5;
				}
				else
				{
						rec.width += 7;
						rec.height += 5;
				}
				imgs.push_back(imgs[i](rec));
		}
		vector<Mat>::iterator iter = imgs.begin();
		for(i = 0; i < length; i++)
				iter = imgs.erase(iter);
		cout << "@: after rotate" << endl;
		for(i = 0; i < imgs.size(); i++)
		{
				imshow(to_string(i), imgs[i]);
				waitKey(1000);
		}
}


void Identifier(int argc, char* argv[])
{
		matrix stand_matrix;
		stand_matrix.test_read();

		vector<Mat> imgs;
		Mat imgOri;
		if (argc == 3)
		{
				Mat half_img = imread(argv[1]);
				Mat another_img = imread(argv[2]);
				addWeighted(half_img, 0.5, another_img, 1.0, 0.5, imgOri);
		}
		else
				imgOri = imread(argv[1]);

		cout << " origin picture" << endl;
		imshow("imgOri", imgOri);
		waitKey(1000);
		gauss(imgOri);
		prepro(imgOri);
		gauss(imgOri);

		cout << "gauss filter completed" << endl;
		imshow("imgOri", imgOri);
		waitKey(1000);
		split(imgOri, imgs);
		//BINARY
		Mat img_bin = imgs.at(2);
		BinImg(img_bin, argc);
		//DILATE
		Mat img_dil;
		Mat temp;
		if(argc != 3)
				temp = getStructuringElement(MORPH_RECT, Size(10,18));
		else
				temp = getStructuringElement(MORPH_RECT, Size(10,15));
		dilate(img_bin, img_dil, temp);
		
		//GETCONTOURS
		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;
		findContours(img_dil, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);

		//DRAWCONTOURS
		int i;
		imgs.clear();
		CleanCon(contours);
		vector<Rect> rec = sort_rec(contours);
		for(i = 0; i < contours.size(); i++)
		{
				imgs.push_back(img_dil(rec[i]));
				cout << "contours" << i << endl;
				imshow(to_string(i), imgs[i]);
				waitKey(1000);
		}
		cout << "total contours" << contours.size() << endl;
		ifRotate(imgs, rec);
		//UNIFORMING SIZE
		vector<Mat> uni_imgs = imgs;
		uniform_size(imgs, uni_imgs);

		vector<vector<int>> value(contours.size(), vector<int>(pix_row * pix_col));
		for(i = 0; i < uni_imgs.size(); i++)
				VecImg(value, uni_imgs[i], i);

		vector<int> numbers;
		cout << endl;
		for(i = 0; i < contours.size(); i++)
				numbers.push_back(stand_matrix.compare(value, i));
		cout << endl << "total number: " ;
		for(i = 0; i < numbers.size(); i++)
				cout << numbers[i];
		cout << endl;
		waitKey(3000);
}


		

		
