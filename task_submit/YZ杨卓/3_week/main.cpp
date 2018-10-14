/*******************************
 * week 3 project: 数字识别
 *
 * @Author:	杨卓
 * @Revised:	杨卓
 * @Version:	1.0.0
 * @Date:	2018-10-14
 */


#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

void filteredRed(const Mat &inputImage, Mat &resultGray);
bool cmp(Rect& a, Rect& b)       { return (a.x < b.x); }
int num_recognition(Mat img);
int num_judge(int count, Mat img);

/**
 * @brief   3-week program main function
 *
 * @param  argc  -- counts of argument
 * @param  argv  -- variables of argument
 *
 * @return integer
 */
int main(int argc, char** argv)
{
  Mat dil;

  if(argc==2)
  {
	Mat src = imread(argv[1]);
	imshow("src", src);
	
	Mat gus;
	GaussianBlur(src, gus, Size(21,21) ,0 ,0);
// 	imshow("gus", gus);

	Mat gry;
	filteredRed(gus, gry);
//	imshow("gry", gry);

	//膨胀（白）
//	Mat dil;
	Mat element_dil = getStructuringElement(MORPH_RECT, Size(7,7) );
	dilate(gry, dil, element_dil);
//	imshow("dil", dil);
  }

  else if(argc==3)
  {
	Mat src1 = imread(argv[1]);
        Mat src2 = imread(argv[2]);
        imshow("src1", src1);
        imshow("src2", src2);

        Mat gus1, gus2;
        GaussianBlur(src1, gus1, Size(21,21) ,0 ,0);
        GaussianBlur(src2, gus2, Size(21,21) ,0 ,0);
//        imshow("gus1", gus1);
//        imshow("gus2", gus2);

        Mat gry1, gry2;
        filteredRed(gus1, gry1);
        filteredRed(gus2, gry2);
//        imshow("gry1", gry1);
//        imshow("gry2", gry2);


        //图片叠加
        double value1 = 1;
        double value2 = 1;
        Mat img_add;
        addWeighted(gry1, value1, gry2, value2, 0.0, img_add);
//       imshow("img_add", img_add);


	//腐蚀（黑）
	Mat ero;
	Mat element_ero = getStructuringElement(MORPH_RECT, Size(5,5));
	erode(img_add, ero, element_ero);
//	imshow("ero", ero);


        //膨胀（白）
        Mat element_dil = getStructuringElement(MORPH_RECT, Size(10,10) );
        dilate(ero, dil, element_dil);
//        imshow("dil", dil);

  }
  
  else
  {
	  cout << "input error!" << endl;
	  return 0;
  }



        vector<vector<Point> > contours;	//存放数字轮廓信息
        vector<Vec4i> hierarchy;

        findContours(dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

//      cout << "contours.size: " << contours.size() << endl;

        const size_t size = contours.size();
        vector<Rect> num_location;	// 存放数字轮廓的边界信息

        for(int i=0; i < contours.size(); i++)
        {
                num_location.push_back(boundingRect(Mat(contours[i])));
        }

	//根据x坐标的大小对数字轮廓信息进行排序
        sort(num_location.begin(), num_location.end(), cmp);


//        cout << "num_location.size: " << num_location.size() << endl;


	vector<Mat> roi_num;	//存放单个数字图像
	vector<int> number;	//存放识别出的数字

  	int row,col;
	for(int i=0; i<num_location.size(); i++)
        {
		Rect r = num_location[i];	
		roi_num.push_back( (dil(r)).clone() );
		
		//数字识别 int num_recognition()
		number.push_back( num_recognition(roi_num[i]) );

//              cout << "第"<< i+1 << "个数为: " << number[i] << endl;

		//在原图像上划出矩形轮廓
        	rectangle(dil, r , Scalar(255), 2);
        	
	}

	
	imshow("第一个数", roi_num[0]);
        imshow("第二个数", roi_num[1]);
        imshow("第三个数", roi_num[2]);
        imshow("第四个数", roi_num[3]);
	imshow("find", dil);
	
	cout << "Final result: " << number[0] << number[1] << number[2] << number[3] << endl;


	waitKey(0);
        return 0;
}       

/**
 * @brief	将输入图片转化为HSV格式，通过选出特定的数字颜色（红色），将数字			从图像中选出，并将其它噪音去除，转化为二值化的图像输出。
 *
 * @param	inputImage -- 原始图像
 * @param	resultGray -- 输出的二值图
 */
void filteredRed(const Mat &inputImage, Mat &resultGray)
{
    Mat hsvImage;
    cvtColor(inputImage, hsvImage, CV_BGR2HSV);
  
    //新建大小和hsvImage一样，但像素全为0的Mat
    resultGray = Mat(hsvImage.rows, hsvImage.cols,CV_8U,cv::Scalar(0));
       
    double H=0.0,S=0.0,V=0.0;
    for(int i=0;i<hsvImage.rows;i++)
    {
        for(int j=0;j<hsvImage.cols;j++)
        {
            H=hsvImage.at<Vec3b>(i,j)[0]; 
	    S=hsvImage.at<Vec3b>(i,j)[1]; 
	    V=hsvImage.at<Vec3b>(i,j)[2];
            
	    if( S >= 225 )
            {	
		//根据数码管红色数字的HSV值设定区域,图像在此区域的像素设定为255
                if( (  H>=0 && H < 5 || H>=145 && H<150)  &&  V >= 110 )
                 {
                    resultGray.at<uchar>(i,j)=255;
                 }
            }
         }
    }
}


/**@brief	输出识别出来的数字
 *
 * @param	img -- 单个分割出来的数字图像
 *
 * @return 	integer -- 数字
 */
int num_recognition(Mat img)
{
	int num = 0;	 // 用于return的数字
	int count = 0;	 // 用于判断数字
	int count255 = 0;// 用于统计像素中255的个数
	int row,col; 	 

	// 1 * 10^0
	count255 = 0; 
	for(row=0; row < img.rows * 1/3; row++)
	{
		if( int(img.at<uchar>(row, img.cols/2)) == 255 )
			count255++;
	}
	if( count255 > ( img.rows * 1/10) )
		count = count + 1*pow(10, 0);


	//2 * 10^1
	count255 = 0;
	bool flag = 1; // 1为255
	for(row=img.rows*7/15; row<=img.rows*8/15; row++)
	{
		for(col=img.cols*4/9; col<=img.cols*5/9; col++)
		{
			if(int(img.at<uchar>(row,col)) == 0)
			{
				flag = 0;
				break;
			}
		}
	}

	if(flag==1)	count = count + 2*pow(10, 1);
	
	
	// 3 * 10^2
	count255 = 0;
        for(row=img.rows * 2/3; row < img.rows; row++)
        {
                if( int(img.at<uchar>( row, img.cols/2)) == 255 )
                        count255++;
        }
        if( count255 > ( img.rows * 1/15) )
                count = count + 3*pow(10, 2);



	// 4 * 10^3
	count255 = 0;
	for(col=0; col < img.cols/2; col++)
	{
		if( int(img.at<uchar>( img.rows/3, col )) == 255 )
			count255++;
	}	
	if(count255 > (img.cols/6) )
		count = count + 4*pow(10, 3);



        // 5 * 10^4
        count255 = 0;
        for(col=img.cols/2; col < img.cols; col++)
        {
                if( int(img.at<uchar>( img.rows/3, col )) == 255 )
                        count255++;
        }
        if(count255 > (img.cols/6) )
                count = count + 5*pow(10, 4);


        // 6 * 10^5
        count255 = 0;
        for(col=0; col < img.cols/2; col++)
        {
                if( int(img.at<uchar>( img.rows * 2/3, col )) == 255 )
                        count255++;
        }
        if(count255 > (img.cols/6) )
                count = count + 6*pow(10, 5);


        // 7 * 10^6
        count255 = 0;
        for(col=img.cols/2; col < img.cols; col++)
        {
                if( int(img.at<uchar>( img.rows * 2/3, col )) == 255 )
                        count255++;
        }
        if(count255 > (img.cols/6) )
                count = count + 7*pow(10, 6);


	cout << "count: " << count << " 对应数字 " ; 
	num = num_judge(count, img);	
	cout << num << endl;
	return num;
}


/**
 * @brief	输出count对应的数字
 *
 * @param	count -- 从单个数字图像中得到的用于判断数字的值
 * @param	img -- 单个数字图像
 *
 * @return 	integer -- 识别出来的数字
 */
int num_judge(int count, Mat img)
{

	int count255 = 0;
	if(count == 7654321)
	{
		for(int row=0; row<img.rows; row++)
		{
			if(int(img.at<uchar>(row, img.cols/2)) == 255)
				count255++;
		}

		if( count255 > (img.rows * 9/10) )	
			return 1;

		else 	return 8;

	}

	        switch(count)
        {
                case 7654301:   return 0;       break;
                case 650321:    return 2;       break;
                case 7050321:   return 3;       break;
                case 7054020:   return 4;       break;
                case 7004321:   return 5;       break;
                case 7604321:   return 6;       break;
                case 7050001:   return 7;       break;
                case 7054321:   return 9;       break;
		case 0:		return -1;	break;
	}

		return -1;
}



void drawline(Mat img)
{
	//横线
	Point start1 = Point(0, img.rows * 4/9);
	Point end1 = Point(img.cols, img.rows * 4/9);
	line(img, start1, end1, Scalar(155));

        Point start2 = Point(0, img.rows * 5/9);
        Point end2 = Point(img.cols, img.rows * 5/9);
        line(img, start2, end2, Scalar(155));

	//竖线
        Point start3 = Point( img.cols * 4/9, 0);
        Point end3 = Point(img.cols * 4/9 , img.rows);
        line(img, start3, end3, Scalar(155));

        Point start4 = Point( img.cols * 5/9, 0);
        Point end4 = Point( img.cols * 5/9, img.rows);
        line(img, start4, end4, Scalar(155));

//	imshow("line", img);
}



