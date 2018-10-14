//
//  client.cpp
//  Digit_discern
//
//  Created by 张涵健 on 2018/10/8.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/client.hpp"
Mat client::filter(Mat image, Size size)
{
    Mat result;
    image.copyTo(result);
    Mat channel[3];
    split(image,channel);
    int l =(size.height-1)/2;
    int w =(size.width-1)/2;
    for (int i = l;i < result.rows-l;i ++){
        for (int j =w;j < result.cols-w;j ++){
            for (int ii =0;ii < 3;ii++){
                result.at<Vec3b>(i,j)[ii]=saturate_cast<uchar>(filter_har(channel[ii](Rect(j-w,i-l,size.width,size.height))));
            }
        }
    }
    return result;
}

void complete(Mat& src){
    for(int x = 0; x < src.rows; x++){
        for(int y = src.cols/2 -2; y < src.cols/2 +16; y++){

            src.at<Vec3b>(x, y)[0] = 255;
            src.at<Vec3b>(x, y)[1] = 255;
            src.at<Vec3b>(x, y)[2] = 255;

        }
    }
    for(int x = 0; x < 32; x++){
        for(int y = 0; y < src.cols; y++){

            src.at<Vec3b>(x, y)[0] = 255;
            src.at<Vec3b>(x, y)[1] = 255;
            src.at<Vec3b>(x, y)[2] = 255;

        }
    }
}


client::client(){

}
void client::open(string a){
    src_name = a;
}
void client::test_1(){
    Mat srcImage1 = imread(src_name);
    Mat dstImage, grayImage, Image;
    imshow("src",srcImage1);
    waitKey(1);
    srcImage1.copyTo(dstImage);
    Mat srcImage = filter(srcImage1, Size(3,3));
    //imshow("filter",srcImage);
    //waitKey(1);
    take_red(srcImage, 180, 150, 150);

    imshow("deal",srcImage);
    waitKey(1);

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);


    threshold(grayImage, Image, 48, 255, CV_THRESH_BINARY_INV);

    /* draw contours */
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(Image,contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(dstImage, contours, -1, (static_cast<void>(255),static_cast<void>(255),255) );
    //imshow("contours",dstImage);
    //waitKey(1);

    /* find min contours closed rect for numbers */
    int i = 0;
    Point2f pp[5][4];
    Rect rect[10];
    vector<vector<Point> >::iterator It;
    for(It = contours.begin();It < contours.end();It++){
        Point2f vertex[4];
        rect[i] = boundingRect(*It);
        vertex[0] = rect[i].tl();
        static_cast<void>(vertex[1].x = (float)rect[i].tl().x), vertex[1].y = (float)rect[i].br().y;
        vertex[2] = rect[i].br();
        static_cast<void>(vertex[3].x = (float)rect[i].br().x), vertex[3].y = (float)rect[i].tl().y;


        for( int j = 0; j < 4; j++)
            line(dstImage, vertex[j], vertex[ (j+1)%4 ],Scalar(0,0,255),1);

        /* Find the central point's position for rect */
        con[i].x = (vertex[0].x+vertex[1].x+vertex[2].x+vertex[3].x) / 4.0;                  
        con[i].y = (vertex[0].y+vertex[1].y+vertex[2].y+vertex[3].y) / 4.0;
        con[i].order = i;
        if(rect[i].area()>300)
            i++;
    }
    sort(con,con+i);

    /*----------------------Draw RECT--------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        rectangle(dstImage,rect[k],Scalar(255,255,255),3,8,0);
    }
    imshow("RECT",dstImage);
    waitKey(1);

    /*—----------------------------------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        srcImage(rect[k]).copyTo(num[j]);
        cvtColor(num[j], num[j], COLOR_BGR2GRAY);
        threshold(num[j], num[j], 48, 255, CV_THRESH_BINARY_INV);
        //imshow("aaa",num[j]);
        //waitKey(1);

        deal(num[j],j+1);
    }

}

void client::test_2(){
    Mat srcImage1 = imread(src_name);
    Mat dstImage, grayImage, Image;
    Mat srcImage = filter(srcImage1, Size(3,3));
    imshow("???",srcImage1);
    waitKey(1);

    //Rect rec(220, 200 , 350, 200);
    //Mat srcImage = srcImage1(rec);
    srcImage.copyTo(dstImage);
    take_red(srcImage, 205, 215, 215);
    complete(srcImage);

    imshow("SRC",srcImage);
    waitKey(1);

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);


    threshold(grayImage, Image, 48, 255, CV_THRESH_BINARY_INV);

    /* draw contours */
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(Image,contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(dstImage, contours, -1, (static_cast<void>(255),static_cast<void>(255),255) );
    //imshow("av",dstImage);
    //waitKey(1);

    /* find min contours closed rect for numbers */
    int i = 0;
    Point2f pp[5][4];
    Rect rect[10];
    vector<vector<Point> >::iterator It;
    for(It = contours.begin();It < contours.end();It++){
        Point2f vertex[4];
        rect[i] = boundingRect(*It);
        vertex[0] = rect[i].tl();
        static_cast<void>(vertex[1].x = (float)rect[i].tl().x), vertex[1].y = (float)rect[i].br().y;
        vertex[2] = rect[i].br();
        static_cast<void>(vertex[3].x = (float)rect[i].br().x), vertex[3].y = (float)rect[i].tl().y;


        for( int j = 0; j < 4; j++)
            line(dstImage, vertex[j], vertex[ (j+1)%4 ],Scalar(0,0,255),1);

        /* Find the central point's position for rect */
        con[i].x = (vertex[0].x+vertex[1].x+vertex[2].x+vertex[3].x) / 4.0;
        con[i].y = (vertex[0].y+vertex[1].y+vertex[2].y+vertex[3].y) / 4.0;
        con[i].order = i;
        if(rect[i].area()>900)
            i++;
    }
    sort(con,con+i);

    /*----------------------Draw RECT--------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        rectangle(dstImage,rect[k],Scalar(255,255,255),3,8,0);
    }
    imshow("RECT",dstImage);
    waitKey(1);


    /*-----------------------------------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        srcImage(rect[k]).copyTo(num[j]);
        cvtColor(num[j], num[j], COLOR_BGR2GRAY);
        threshold(num[j], num[j], 48, 255, CV_THRESH_BINARY_INV);
        //imshow("aaa",num[j]);
        //waitKey(1);

        deal(num[j],j+1);
    }

}



void client::test_3(string n1,string n2){
    Mat srcImage1 = imread(n1);
    Mat srcImage2 = imread(n2);
    imshow("src_1",srcImage1);
    waitKey(1);
    imshow("src_2",srcImage2);
    waitKey(1);
    Mat dstImage, grayImage, Image;
    Mat srcImage;
    combine(srcImage1, srcImage2).copyTo(srcImage);
    //imshow("src_c",srcImage);
    //waitKey(1);
    srcImage.copyTo(dstImage);
    take_red(srcImage, 180, 150, 150);
    imshow("SRC",srcImage);
    waitKey(1);

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);


    threshold(grayImage, Image, 48, 255, CV_THRESH_BINARY_INV);

    /* draw contours */
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(Image,contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(dstImage, contours, -1, (static_cast<void>(255),static_cast<void>(255),255) );
    //imshow("av",dstImage);
    //waitKey(1);

    /* find min contours closed rect for numbers */
    int i = 0;
    Point2f pp[5][4];
    Rect rect[10];
    vector<vector<Point> >::iterator It;
    for(It = contours.begin();It < contours.end();It++){
        Point2f vertex[4];
        rect[i] = boundingRect(*It);
        vertex[0] = rect[i].tl();
        static_cast<void>(vertex[1].x = (float)rect[i].tl().x), vertex[1].y = (float)rect[i].br().y;
        vertex[2] = rect[i].br();
        static_cast<void>(vertex[3].x = (float)rect[i].br().x), vertex[3].y = (float)rect[i].tl().y;


        for( int j = 0; j < 4; j++)
            line(dstImage, vertex[j], vertex[ (j+1)%4 ],Scalar(0,0,255),1);

        /* Find the central point's position for rect */
        con[i].x = (vertex[0].x+vertex[1].x+vertex[2].x+vertex[3].x) / 4.0;
        con[i].y = (vertex[0].y+vertex[1].y+vertex[2].y+vertex[3].y) / 4.0;
        con[i].order = i;
        if(rect[i].area()>700)
            i++;
    }
    sort(con,con+i);


    /*----------------------Draw RECT--------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        rectangle(dstImage,rect[k],Scalar(255,255,255),3,8,0);
    }
    imshow("RECT",dstImage);
    waitKey(1);


    /*-----------------------------------------------*/
    for(int j = 0; j < i; j++){
        int k = con[j].order;
        srcImage(rect[k]).copyTo(num[j]);
        cvtColor(num[j], num[j], COLOR_BGR2GRAY);
        threshold(num[j], num[j], 48, 255, CV_THRESH_BINARY_INV);
        //imshow("aaa",num[j]);
        //waitKey(1);

        deal(num[j],j+1);
    }

}




void client::deal(Mat &src,int order){

    Mat sample;

    //imshow("src",src);
    //waitKey(1);

    sample = imread("../data/num_sam/0.jpg");
    Threshold(src,sample,0);

    sample = imread("../data/num_sam/1.jpg");
    Threshold(src,sample,1);

    sample = imread("../data/num_sam/2.jpg");
    Threshold(src,sample,2);

    sample = imread("../data/num_sam/3.jpg");
    Threshold(src,sample,3);

    sample = imread("../data/num_sam/4.jpg");
    Threshold(src,sample,4);

    sample = imread("../data/num_sam/5.jpg");
    Threshold(src,sample,5);

    sample = imread("../data/num_sam/6.jpg");
    Threshold(src,sample,6);

    sample = imread("../data/num_sam/7.jpg");
    Threshold(src,sample,7);

    sample = imread("../data/num_sam/8.jpg");
    Threshold(src,sample,8);

    sample = imread("../data/num_sam/9.jpg");
    Threshold(src,sample,9);

    sort(_result,_result+10);

    if(_result[9].bi > 0.6) {
        //cout << "第" << order << "个数字为 "<< _result[9]. num<<endl;
        //cout << "识别精度为 " << _result[9].bi <<endl;
        /*
        if (_result[9].num == 1){
            if (_result[9].bi >0.79)
                cout << _result[9].num;
        }

        else
         */
            cout << _result[9].num;
    }
    //else cout << "第" << order << "个数字无法识别"<<endl;
}

void client::Threshold(Mat &src,Mat &sample,int m){
    cvtColor(sample, sample, COLOR_BGR2GRAY);
    threshold(sample, sample, 48, 255, CV_THRESH_BINARY_INV);
    _result[m].bi = compare(src,sample);
    _result[m].num = m;
}

double client::compare(Mat &src, Mat &sample){
    double same = 0.0, difPoint = 0.0;
    Mat now;
    resize(sample,now,src.size());
    //imshow("now",now);
    //waitKey(1);
    int row = now.rows;
    int col = now.cols *  now.channels();
    for(int i = 0; i < 1; i++){
        uchar * data1 = src.ptr<uchar>(i);
        uchar * data2 = now.ptr<uchar>(i);
        for(int j = 0; j < row * col; j++){
            int a = data1[j];
            int b = data2[j];
            if( a == b ) same++;
            else difPoint++;
        }
    }
    return same/(same+difPoint) ;
}

void client::take_red(Mat &src, int r_level, int b_level, int g_level){
    for(int x = 0; x < src.rows; x++){
        for(int y = 0; y < src.cols; y++){
            int b = src.at<Vec3b>(x, y)[0];
            int g = src.at<Vec3b>(x, y)[1];
            int r = src.at<Vec3b>(x, y)[2];

            if (r > r_level && r > b && r > g && b<b_level && g<g_level){
                if(x >=  OW+9 && y >= OW+1){
                    for (int i = 0; i < OW+9; i++){
                        for (int j = 0; j < OW+1 ; j++){
                            src.at<Vec3b>(x - i, y - j)[0] = 0;
                            src.at<Vec3b>(x - i, y - j)[1] = 0;
                            src.at<Vec3b>(x - i, y - j)[2] = 0;
                        }
                    }
                }

            }
            else{
                src.at<Vec3b>(x, y)[0] = 255;
                src.at<Vec3b>(x, y)[1] = 255;
                src.at<Vec3b>(x, y)[2] = 255;
            }
        }
    }
    //imshow("qwe",src);
    //complete(src,10);
}



Mat client::combine(Mat& src1, Mat& src2){
    Mat re;
    src1.copyTo(re);
    for (int i = 0; i<src1.rows; i++){
        for(int j = 0; j<src1.cols; j++){

            int B = src2.at<Vec3b>(i, j)[0];
            int G = src2.at<Vec3b>(i, j)[1];
            int R = src2.at<Vec3b>(i, j)[2];

            if(R > 200 && G < 60 && B < 60){
                re.at<Vec3b>(i, j)[0] = B;
                re.at<Vec3b>(i, j)[1] = G;
                re.at<Vec3b>(i, j)[2] = R;
            }

        }
    }
    return re;

}

void client::test(){
    if (src_name.substr(4,3).compare("sim"))
        test_1();

    else
        test_2();
}

