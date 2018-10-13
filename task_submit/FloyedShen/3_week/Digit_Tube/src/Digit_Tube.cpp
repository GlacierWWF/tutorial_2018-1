/*********************************************************
 * Digit_Tube image Recognition by opencv
 *
 * @author	Floyed_Shen
 * @email	Floyed_Shen@outlook.com
 * @version	1.0.0
 * @date	2018/10/12
 *********************************************************/
#define DRAW_RES //绘制图像
//#define DEBUG_DIGIT_TUBE //调试使用
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "../inc/Digit_Tube.h"
bool cmp_area(cv::Rect x,cv::Rect y){
    return x.area()>y.area();
}
bool cmp_height(cv::Rect x,cv::Rect y){
    return x.height>y.height;
}
bool cmp_tl(cv::Rect x,cv::Rect y){
    return x.tl().x<y.tl().x;
}
bool cmp_dis1(cv::Point2f a,cv::Point2f b){
    return (a.x+a.y)<(b.x+b.y);
}
Digit_Tube::Digit_Tube(){
    model=0;
    x=205,y=200,z_ero=6,z_dil=4,g=5;
    mt=cv::Mat(1,1,CV_8SC1);
}
Digit_Tube::Digit_Tube(cv::Mat x){
    model=0;
    x=205,y=200,z_ero=6,z_dil=4,g=5;
    mt=x.clone();
}
Digit_Tube::Digit_Tube(char s[]){
    model=0;
    x=205,y=200,z_ero=6,z_dil=4,g=5;
    mt=cv::imread(s);
    //cv::cvtColor(mt,bin,CV_RGB2GRAY);
}
Digit_Tube::Digit_Tube(std::string s){
    model=0;
    x=205,y=200,z_ero=6,z_dil=4,g=5;
    mt=cv::imread(s);
}
Digit_Tube::Digit_Tube(std::string s1,std::string s2){//new
    model=1;
    x=205,y=200,z_ero=6,z_dil=4,g=5;
    comb1=cv::imread(s1);
    comb2=cv::imread(s2);
}
Digit_Tube::~Digit_Tube(){}
bool Digit_Tube::open()const{
    if(model==0){
        if(mt.data)
            return 1;
        return 0;
    }
    if(model==1){
        if(comb1.data&&comb2.data)
            return 1;
        return 0;
    }
}
void Digit_Tube::print()const{
    for(int i=0;i<ans.size();i++){
        printf("%d ",ans[i]);
    }putchar('\n');
}
float Digit_Tube::calc_bin(cv::Mat x)const{
    int tot_black=0;
    for(int i=0;i<x.rows;i++)
        for(int j=0;j<x.cols;j++){
            if(x.at<uchar>(i,j)==0)
                tot_black++;
        }
    float ans=float(tot_black)/float(x.rows*x.cols);
#ifdef DEBUG_DIGIT_TUBE
    printf("%f\n",ans);
#endif
    return ans;
}
void Digit_Tube::rotate(cv::Mat &src){
    cv::Mat src_gray,src_bin;
	cv::cvtColor(src,src_bin,CV_BGR2GRAY);
	threshold(src_bin, src_bin, 0, 255, CV_THRESH_OTSU);//自适应二值化
	src_bin = 255 - src_bin;//颜色反转
	//imshow("src_bin", src_bin);
	//寻找最外层轮廓
	std::vector<std::vector<cv::Point> >contours;
	std::vector<cv::Vec4i>hierarchy;
	cv::findContours(src_bin,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE,cv::Point());
    cv::Point2f srcTri[3];//原图坐标
    cv::Point2f dstTri[3];//映射之后的坐标
    cv::Mat warp_mat(2,3,CV_32FC1);
    cv::Mat warp_dst;

	//cv::Mat drawing = cv::Mat::zeros(src_bin.size(), CV_8UC1); //最小外接矩形drawing
	//sort(contours.begin(),contours.end(),cmp_rotate_area);
	//cout<<"deal";
	int index=0;
	cv::Point2f point[4];
	cv::RotatedRect rect;
	while(index<contours.size()){
		rect = minAreaRect(contours[index]);
		rect.points(point);
		std::sort(point,point+4,cmp_dis1);
		if(point[2].x-point[0].x>src.cols/4)//寻找大小合适的任意四边形
			break;
		index++;
	}
		//绘制轮廓
		//drawContours(drawing, contours, i, Scalar(255), 1, 8, hierarchy);
		//float area=abs(contours[i][1].x*contours[i][2].y+contours[i][2].x*contours[i][3].y+contours[i][3].x*contours[i][1].y-contours[i][1].x*contours[i][3].y-contours[i][2].x*contours[i][1].y-contours[i][3].x*contours[i][2].y);
		//cout<<area<<endl;
		//绘制轮廓的最小外结矩形

		//rectangle(drawing,rect.boundingRect(),Scalar(55));
		/*for (int j = 0; j <= 3; j++)
		{
			line(src, P[j], P[(j + 1) % 4], Scalar(255,255,255), 1);
			line(drawing, P[j], P[(j + 1) % 4], Scalar(111), 2);
		}*/
    warp_dst=cv::Mat::zeros( src.rows, src.cols, src.type() );
    srcTri[0]=point[0];
    srcTri[1]=point[1];
    srcTri[2]=point[3];

    dstTri[0]=cv::Point2f(0,0);
    dstTri[1]=cv::Point2f(0,src.rows);
    dstTri[2]=cv::Point2f(src.cols,src.rows);

    warp_mat=cv::getAffineTransform(srcTri,dstTri);// 求得仿射变换

    warpAffine(src,warp_dst,warp_mat,warp_dst.size());// 对源图像应用上面求得的仿射变换
        /*
		//绘制轮廓的最小外结圆
		Point2f center; float radius;
		minEnclosingCircle(contours[i], center, radius);
		circle(drawing1, center, radius, Scalar(255), 2);
        */
    src=warp_dst.clone();//赋值给原图
    //cv::imshow("dst",src);
    //cv::waitKey(1);
    //getchar();
	//imshow("最小外接矩形", drawing);
	//imshow("标注出矩形", src);
	//waitKey(0);
}
void Digit_Tube::add(){
    bin=255-((255-bin1)+(255-bin2));//取交集/或者说取黑色部分的并集
}
void Digit_Tube::pre_solve(cv::Mat &src){
    cv::GaussianBlur(src,src,cv::Size(g,g),0,0);//高斯滤波
    //cv::imshow("src",src);
    //cv::waitKey(0);
    std::vector<cv::Mat>channels;
    cv::split(src,channels);//通道分离
    red=channels.at(2).clone();
    green=channels.at(1).clone();
    blue=channels.at(0).clone();
    //cv::equalizeHist(red,red);//直方图均值化    /*会降级识别率*/
    //cv::equalizeHist(green,green);
    //cv::equalizeHist(blue,blue);
    //cv::imshow("gray",src_gray);
    gray2bin();
}
void Digit_Tube::gray2bin(){
    cv::Mat a,b,c;
    cv::threshold(green,b,y,255,0);//二值化
    cv::threshold(blue,c,y,255,0);//二值化
    if(1-calc_bin(b)<1e-3&&1-calc_bin(c)<1e-3){
        cv::threshold(red,a,x-50,255,1);//二值化
        bin=a.clone();
    }else{
        cv::threshold(red,a,x,255,1);//二值化
        bin=a+b+c;
    }
#ifdef DEBUG_DIGIT_TUBE
    cv::imshow("r",a);
    cv::imshow("g",b);
    cv::imshow("b",c);
#endif
    cv::Mat ero,dil;//腐蚀膨胀

    cv::Mat element_ero=cv::getStructuringElement(2,cv::Size(z_ero*2+1,z_ero*2+1),cv::Point(z_ero,z_ero));
    cv::Mat element_dil=cv::getStructuringElement(2,cv::Size(z_dil*2+1,z_dil*2+1),cv::Point(z_dil,z_dil));
    cv::erode(bin,bin,element_ero);
    cv::dilate(bin,bin,element_dil);
#ifdef DEBUG_DIGIT_TUBE
    cv::imshow("bin",bin);
#endif
}
void Digit_Tube::img_divide(){
    cv::Mat threshold_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
/// 使用Threshold检测边缘
    threshold(bin,threshold_output,254,255,cv::THRESH_BINARY);
    /// 找到轮廓
    findContours(threshold_output,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,cv::Point(0,0));
    /// 多边形逼近轮廓 + 获取矩形和圆形边界框
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size());
    std::vector<cv::Point2f>center( contours.size());
    std::vector<float>radius( contours.size() );
    for(int i=0;i<contours.size();i++){
        approxPolyDP(cv::Mat(contours[i]),contours_poly[i],3,true);
        boundRect[i]=cv::boundingRect(cv::Mat(contours_poly[i]));
        cv::minEnclosingCircle(contours_poly[i],center[i],radius[i]);
    }

    std::sort(boundRect.begin(),boundRect.end(),cmp_height);

    std::vector<cv::Rect>rect_tmp;
    int height_max=boundRect[1].height;
    int index=1,tot=0;
    while(tot<4){
#ifdef DEBUG_DIGIT_TUBE
        std::cout<<height_max<<' '<<boundRect[index].height<<' '<<tot<<' '<<index<<std::endl;
#endif
        if(boundRect[index].height*3/2<height_max){
            rect_tmp.push_back(boundRect[index]);
            index++;
        }
        tot++;
        rect_tmp.push_back(boundRect[index]);
        index++;
    }
    sort(rect_tmp.begin(),rect_tmp.end(),cmp_tl);

    std::vector<cv::Rect>rect;
    for(int i=0;i<rect_tmp.size();i++){
        if(rect_tmp[i].height*3/2<height_max){
            //std::cout<<rect_tmp[i].height<<' '<<height_max<<"fuck"<<std::endl;
            rect.push_back(rect_tmp[i]|rect_tmp[i+1]);
            i++;
        }else
            rect.push_back(rect_tmp[i]);
    }
#ifdef DEBUG_DIGIT_TUBE
    std::vector<cv::Mat> _debug;
    std::string s[10]={"1","2","3","4","5","6","7","8","9","10"};
    for(int i=0;i<rect_tmp.size();i++){
        _debug.push_back(bin(cv::Range(rect_tmp[i].tl().y,rect_tmp[i].br().y),cv::Range(rect_tmp[i].tl().x,rect_tmp[i].br().x)));
        //cv::resize(_debug[i],_debug[i],cv::Size(64,128),0,0,CV_INTER_AREA);
        cv::imshow(s[i],_debug[i]);
        cv::waitKey(100);
        getchar();
    }
#endif
    for(int i=0;i<rect.size();i++){
        num.push_back(bin(cv::Range(rect[i].tl().y,rect[i].br().y),cv::Range(rect[i].tl().x,rect[i].br().x)));
        cv::resize(num[i],num[i],cv::Size(64,128),0,0,CV_INTER_AREA);
#ifdef DEBUG_DIGIT_TUBE
        cv::imshow(s[i],num[i]);
        cv::waitKey(100);
        //getchar();
#endif
    }
#ifdef DRAW_RES
    ///画多边形轮廓 + 包围的矩形框
    cv::Mat drawing=bin.clone();
    for(int i=0;i<rect.size();i++){
        cv::Scalar color=cv::Scalar(0,0,0);
        //cv::drawContours(drawing,contours_poly,i,color,1,8,std::vector<cv::Vec4i>(),0,cv::Point());
        cv::rectangle(drawing,rect[i].tl(),rect[i].br(),color,2,8,0);
        //cv::circle(drawing,center[i],(int)radius[i],color,2,8,0);
        cv::namedWindow("DIVIDE_RES",CV_WINDOW_AUTOSIZE);
        cv::imshow("DIVIDE_RES",drawing);
    }
#endif
}
void Digit_Tube::num_divide(){
    int x=num[0].cols/3,y=num[0].rows/5;
#ifdef DEBUG_DIGIT_TUBE
    std::string s[10]={"1","2","3","4","5","6","7","8","9","10"};
#endif
    for(int k=0;k<num.size();k++){
        std::vector<cv::Mat>sub_num;
        for(int i=0;i<5;i++){
            if(i%2){
                sub_num.push_back(num[k](cv::Range(i*y,(i+1)*y),cv::Range(0,x)));
                sub_num.push_back(num[k](cv::Range(i*y,(i+1)*y),cv::Range(2*x,3*x)));
            }else
                sub_num.push_back(num[k](cv::Range(i*y,(i+1)*y),cv::Range(x,2*x)));
        }
        sub_num.push_back(num[k](cv::Range(1*y,(2+1)*y),cv::Range(x,2*x)));
        for(int i=0;i<sub_num.size()-1;i++){
#ifdef DEBUG_DIGIT_TUBE
            cv::imshow(s[i],sub_num[i]);
#endif
            if(calc_bin(sub_num[i])>0.2){
                digit_res[k].push_back(true);
                //std::cout<<i<<std::endl;
            }
            else digit_res[k].push_back(false);
        }
        if(calc_bin(sub_num[7])>0.55)
            digit_res[k].push_back(1);
        else
            digit_res[k].push_back(0);
#ifdef DEBUG_DIGIT_TUBE
        putchar('\n');
#endif
        //cv::waitKey(0);
    }

}
void Digit_Tube::translate(){
    for(int k=0;k<4;k++){
        if(digit_res[k][7]){
            ans.push_back(1);
            continue;
        }
        if(!digit_res[k][0]&&(digit_res[k][1])){
            ans.push_back(4);
            continue;
        }
        if(!digit_res[k][2]&&!digit_res[k][4]){
            ans.push_back(5);
            continue;
        }
        if((!digit_res[k][6]&&!digit_res[k][3])||(!digit_res[k][1]&&!digit_res[k][3]&&!digit_res[k][4])){
            ans.push_back(7);
            continue;
        }
        if(!digit_res[k][3]){
            ans.push_back(0);
            continue;
        }
        if(!digit_res[k][1]&&!digit_res[k][5]){
            ans.push_back(2);
            continue;
        }
        if(!digit_res[k][1]&&!digit_res[k][4]){
            ans.push_back(3);
            continue;
        }
        if(!digit_res[k][2]){
            ans.push_back(6);
            continue;
        }
        if(!digit_res[k][4]){
            ans.push_back(9);
            continue;
        }
        if(digit_res[k][3]){
            ans.push_back(8);
            continue;
        }
        ans.push_back(-1);
    }
}
void Digit_Tube::identify(){
    if(model==1){
        rotate(comb1);
#ifdef DEBUG_DIGIT_TUBE
        cv::imshow("1",comb1);
        cv::waitKey(1);
#endif
        rotate(comb2);
#ifdef DEBUG_DIGIT_TUBE
        cv::imshow("2",comb2);
        cv::waitKey(1);
#endif
        pre_solve(comb1);
        bin1=bin.clone();

        pre_solve(comb2);
        bin2=bin.clone();

        add();
#ifdef DEBUG_DIGIT_TUBE
        cv::imshow("comb",bin);
        cv::waitKey(1);
        getchar();
#endif
    }else if(model==0){
        pre_solve(mt);
    }
#ifdef DEBUG_DIGIT_TUBE
    std::cout<<calc_bin(green)<<std::endl;
    std::cout<<calc_bin(blue)<<std::endl;
#endif
    img_divide();
    num_divide();
    translate();
}