/******************************************************************
 * @file	fun.cpp
 * @brief	This file define some functions used in the project
 * Details.
 *
 * @version	1.0.1
 * @author	Lomgahong
 * @email	1073097404@qq.com
 *
 * -----------------------------------------------------------------
 *  Change History:
 *  <Date>	|<Version>	|<Author>	|<Description>
 *  ----------------------------------------------------------------
 *  2018/10/14	|1.0.1		|Lomgahong	|Create file
 *
 *  ****************************************************************/

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"fun.hpp"

using namespace std;
using namespace cv;

//用于判断两个矩形的宽度哪一个更宽
bool cmp(const Rect& a,const Rect& b)
{
	return(a.x<b.x);
}
                                  
/**
 *用于读取数字的函数
 *原理：每个区域对应七位数码管的一根管
 *	通过检查区域内黑白点的数目来判断数码管是否为亮
 */

int getnumber(Rect rect,Mat IMAGE)
{
	int x,y,w,h;
	int m,n,i,sum=0,B=0,W=0;
	x=rect.x;
	y=rect.y;
	w=rect.width;
	h=rect.height;
	if(h/(h-w)>4)
		w=w*2/3;
	int record[7];
	int color;
	//0的读取
	for(m=y;m<y+h/5;m++)
	{
		color=IMAGE.at<uchar>(m,x+w/2);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[0]=1;
	else
		record[0]=0;
	B=0;
	W=0;	
//	cout<<record[0];
	//1
	for(n=x+w*4/5;n<x+w;n++)
	{
		color=IMAGE.at<uchar>(y+h/4,n);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[1]=1;
	else
		record[1]=0;
	B=0;
	W=0;	
//	cout<<record[1];	
	//2
	for(n=x+w*4/5;n<x+w;n++)
	{
		color=IMAGE.at<uchar>(y+h*3/4,n);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[2]=1;
	else
		record[2]=0;
	B=0;
	W=0;	
//	cout<<record[2];
	//3
	for(m=y+h*4/5;m<y+h;m++)
	{
		color=IMAGE.at<uchar>(m,x+w/2);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[3]=1;
	else
		record[3]=0;
	B=0;
	W=0;	
//	cout<<record[3];
	//4
	for(n=x;n<x+w/5;n++)
	{
		color=IMAGE.at<uchar>(y+h*3/4,n);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[4]=1;
	else
		record[4]=0;
	B=0;
	W=0;	
//	cout<<record[4];
	//5
	for(n=x;n<x+w/5;n++)
	{
		color=IMAGE.at<uchar>(y+h/4,n);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[5]=1;
	else
		record[5]=0;
	B=0;
	W=0;	
//	cout<<record[5];
	//6
	for(m=y+h*2/5;m<y+h*3/5;m++)
	{
		color=IMAGE.at<uchar>(m,x+w/2);
		if(color>100)
			W++;
		else
			B++;
	}
	if(W>B)	
		record[6]=1;
	else
		record[6]=0;
	B=0;
	W=0;	
//	cout<<record[6]<<endl;
	//将二进制码转化成十进制码
	for(i=0;i<7;i++)
	{
		sum=sum+record[i]*pow(2,i);
//		cout<<":"<<sum<<endl;
	}
	//这条语句避免了1的错误识别
	if((h/w)>3)
		sum=0;
	return sum;
}

/**
 * 这个函数判断某个十进制码对应的一个数字
 */
void transform(int* A)
{
	int i,n;
	for(i=0;i<4;i++)
	{
		n=A[i];
		if(n==63)
			A[i]=0;
		else if(n==0)
			A[i]=1;
		else if(n==91)
			A[i]=2;
		else if(n==79)
			A[i]=3;
		else if(n==102)
			A[i]=4;
		else if(n==109)
			A[i]=5;
		else if(n==125)
			A[i]=6;	
		else if(n==7)
			A[i]=7;
		else if(n==127)
			A[i]=8;
		else if(n==111)
			A[i]=9;
		else 
			break;
	}
}
