
/***********************************************************************
*
*  
*
*  @file       tell_digital.cpp
*  @brief      主要处理的数字识别
*
*
*  @author     马飞鹏
*  @email      767102280@qq.com
*  @version    1.0.0
*  @date       2018/10/14
*
*
*  ------------------------------------------------------------
*  修改历史：
*  ------------------------------------------------------------
*  <日期>    |  <版本> |  <作者>  |  <描述>
*  ------------------------------------------------------------
*  2018/10/14 |  1.0.0  |  马飞鹏  | 创建文件
*  ------------------------------------------------------------
*  2018/10/15 |  1.0.1  |  马飞鹏  | 添加函数cut_picture(Mat &picture)
*  ------------------------------------------------------------
*/

#include "tell_digital.h"

/*
 * @brief  该函数用来切割出可用的识别图像
 * @param  要识别的图像
 * @retval 无
 *
 */
int cut_picture(Mat &picture)
{

	 int cut;
	 int a,b,c;//flag
 	 int c1=0;
	 int height=picture.rows;
	 int width=picture.cols;
	 int c2=width-1;
	 int r1=0;
	 int r2=height-1;
	 threshold(picture,picture,100,255,THRESH_BINARY);
         //dilate(picture,picture,element);
	 for(c1=0;c1<width/2;c1++)
 	{
		cut=0;
 		a=0;
		b=0;
		c=0;
 		for (int j=0;j<height;j++)
 		{
	 		int white=picture.at<uchar>(j,c1);
   	 		white/=255;
    	 		cut+=white;
 		}
	 	if(cut>5)
    			a=1;
    		cut=0;
		for (int j=0;j<height;j++)
 		{
	 		int white=picture.at<uchar>(j,c1+1);
   	 		white/=255;
    	 		cut+=white;
 		}
 		if(cut>5)
     			b=1;
   		cut=0;
 		for (int j=0;j<height;j++)
 		{
	 		int white=picture.at<uchar>(j,c1+2);
    	 		white/=255;
    	 		cut+=white;
 		}
 		if(cut>5)
     			c=1;
		cut=0;
		if (a+b+c>2)
    		break;
 		}
 
 for(int c2=width-1;c2>3;c2--)
 {	
	cut=0;
 	a=0;
	b=0;
	c=0;
 	for (int j=0;j<height;j++)
 	{
		int white=picture.at<uchar>(j,c2);
    		white/=255;
    		cut+=white;
 	}
	if(cut>5)
    		a=1;
	cut=0;
 	for (int j=0;j<height;j++)
 	{
		int white=picture.at<uchar>(j,c2-1);
		white/=255;
    		cut+=white;
 	}
	if(cut>5)
		b=1;
	cut=0;
	for(int j=0;j<height;j++)
 	{
		int white=picture.at<uchar>(j,c2-2);
    		white/=255;
    		cut+=white;
 	}
	if(cut>5)
     		c=1;
    	cut=0;
 	if (a+b+c>2)
    		break;
 }
 for(int r1=0;r1<height/2;r1++)
 {
	 cut=0;
	 a=0;
	 b=0;
	 c=0;
 	for (int j=0;j<width;j++)
 	{
		int white=picture.at<uchar>(r1,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     		a=1;
    	cut=0;
 	for(int j=0;j<width;j++)
 	{
		int white=picture.at<uchar>(r1+1,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     		b=1;
    	cut=0;
    	for (int j=0;j<width;j++)
 	{
		int white=picture.at<uchar>(r1+2,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     		c=1;
    	cut=0;
 	if (a+b+c>2)
    	break;
 	}
 
 for(int r2=height-1;r2>height/2;r2--)
 {
	cut=0;
	a=0;
	b=0;
	c=0;
 	for(int j=0;j<width;j++)
 	{
	 	int white=picture.at<uchar>(r2,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     	a=1;
    	cut=0;
 	for (int j=0;j<width;j++)
 	{
		int white=picture.at<uchar>(r2-1,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     		b=1;
    	cut=0;
   	for(int j=0;j<width;j++)
 	{
		int white=picture.at<uchar>(r2-2,j);
    		white/=255;
    		cut+=white;
    	}
 	if(cut>5)
     		c=1;
    	cut=0;
 	if(a+b+c>2)
    		break;
 }

Rect rect(c1,r1,c2-c1,r2-r1);
picture=picture(rect);
Mat element = getStructuringElement(MORPH_RECT,Size(3,5));
resize(picture,picture,Size(85,150));
threshold(picture,picture,100,255,THRESH_BINARY);
dilate(picture,picture,element);

}
/*
 * @brief  该函数用来识别输入二值图的数字
 * @param  要识别的图像
 * @retval 识别出来的数字
 *
 */
int tell_num(Mat picture)
{

int width=picture.cols;
if(width<60)
{
	return 1;
}
/*********穿线法1***********/
cut_picture(picture);

/*
namedWindow("k",1);
imshow("k",picture);
waitKey(0);
int line =0;
for(int i=0;i<150;i++)
{
	for(int j=0;j<85;j++)
	{
		cout<<(int)picture.at<uchar>(i,j)/255;
	}
	cout<<"  "<<line<<endl;
	line++;
}
*/
int row[3]={0,0,0};
int column[4]={0,0,0,0};
int p1_x =35;
int p2_x =35;
int p1_y =40;
int p2_y =100;
int white_p =0;
int thre=5;
for(int i=p1_y;i>0;i--)
{	
	int k =picture.at<uchar>(i,p1_x);
	if(k==255)
		white_p++;
	
}

if(white_p>thre)
	row[0]=1;

white_p=0;


for(int i=p1_y;i<80;i++)
{
	int k =picture.at<uchar>(i,p1_x);
	if(k==255)
		white_p++;

}
if(white_p>thre)
	row[1]=1;

white_p=0;


for(int i=p2_y;i>50;i--)
{
	if((int)picture.at<uchar>(i,p2_x)==255)
		white_p++;

}
if(white_p>thre)
	row[1]=1;

white_p=0;

for(int i=p2_y;i<149;i++)
{
	if((int)picture.at<uchar>(i,p2_x)==255)
		white_p++;

}
if(white_p>thre)
	row[2]=1;

white_p=0;


for(int i=p1_x;i>0;i--)
{
	if((int)picture.at<uchar>(p1_y,i)==255)
		white_p++;

}
if(white_p>thre)
	column[0]=1;

white_p=0;


for(int i=p1_x;i<84;i++)
{
	if((int)picture.at<uchar>(p1_y,i)==255)
		white_p++;

}
if(white_p>thre)
	column[1]=1;

white_p=0;


for(int i=p2_x;i>0;i--)
{
	if((int)picture.at<uchar>(p2_y,i)==255)
		white_p++;

}
if(white_p>thre)
	column[2]=1;

white_p=0;



for(int i=p2_x;i<84;i++)
{
	if((int)picture.at<uchar>(p2_y,i)==255)
		white_p++;

}
if(white_p>thre)
	column[3]=1;

white_p=0;




/*

for(int i=0;i<3;i++)
cout<<row[i]<<" ";
cout<<endl;
for(int i=0;i<4;i++)
cout<<column[i]<<" ";
cout<<endl;
*/
if(row[0]==1&&row[1]==0&&row[2]==1&&column[0]==1&&column[1]==1&&column[2]==1&&column[3]==1)
   return 0;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==0&&column[1]==1&&column[2]==1&&column[3]==0)
   return 2;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==0&&column[1]==1&&column[2]==0&&column[3]==1)
   return 3;
if(row[0]==0&&row[1]==1&&row[2]==0&&column[0]==1&&column[1]==1&&column[2]==0&&column[3]==1)
   return 4;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==1&&column[1]==0&&column[2]==0&&column[3]==1)
   return 5;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==1&&column[1]==0&&column[2]==1&&column[3]==1)
   return 6;
if(row[0]==1&&row[1]==0&&row[2]==0&&column[0]==0&&column[1]==1&&column[2]==0&&column[3]==1)
   return 7;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==1&&column[1]==1&&column[2]==1&&column[3]==1)
   return 8;
if(row[0]==1&&row[1]==1&&row[2]==1&&column[0]==1&&column[1]==1&&column[2]==0&&column[3]==1)
   return 9;  
return 1;


}

