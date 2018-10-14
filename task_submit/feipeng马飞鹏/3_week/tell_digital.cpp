#include "tell_digital.h"
int tell_num(Mat picture)
{

	
	 Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
         resize(picture,picture,Size(85,150));
         threshold(picture,picture,100,255,THRESH_BINARY);
         dilate(picture,picture,element);
         dilate(picture,picture,element);
         dilate(picture,picture,element);
         dilate(picture,picture,element);
         dilate(picture,picture,element);
         dilate(picture,picture,element);
       	 int cut;
	 int a,b,c;//flag
 	 int c1=0;
	 int height=picture.rows;
	 
 int width=picture.cols;
 int c2=width-1;
 int r1=0;
 int r2=height-1;

 for(c1=0;c1<width/2;c1++)
 {cut=0;
 a=0;
 b=0;
 c=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     a=1;
    cut=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1+1);
    white/=255;
    cut+=white;
 }
 if(cut>10)
     b=1;
 cut=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1+2);
    white/=255;
    cut+=white;
 }
 if(cut>10)
     c=1;
 cut=0;
 if (a+b+c>2)
    break;
 }
 
 for(int c2=width-1;c2>3;c2--)
 {cut=0;
 a=0;
 b=0;
 c=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1);
    white/=255;
    cut+=white;
 }
 if(cut>10)
     a=1;
    cut=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1-1);
    white/=255;
    cut+=white;
 }
 if(cut>10)
     b=1;
    cut=0;
 for (int j=0;j<height;j++)
 {int white=picture.at<uchar>(j,c1-2);
    white/=255;
    cut+=white;
 }
 if(cut>10)
     c=1;
    cut=0;
 
 if (a+b+c>2)
    break;
 }
 
 for(int r1=0;r1<height/2;r1++)
 {cut=0;
 a=0;
 b=0;
 c=0;
 for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     a=1;
    cut=0;
 for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1+1,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     b=1;
    cut=0;
    for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1+2,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     c=1;
    cut=0;
 if (a+b+c>2)
    break;
 }
 
 
 
 
 for(int r1=height-1;r1>height/2;r1--)
 {cut=0;
 a=0;
 b=0;
 c=0;
 for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     a=1;
    cut=0;
 for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1-1,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     b=1;
    cut=0;
    for (int j=0;j<width;j++)
 {int white=picture.at<uchar>(r1-2,j);
    white/=255;
    cut+=white;
    }
 if(cut>10)
     c=1;
    cut=0;
 if (a+b+c>2)
    break;
 }

 Rect rect(c1,r1,c2-c1,r2-r1);
 picture=picture(rect);
	int row[3];
	int column[4];
	int spots;
double rate=0.95;
double rate1=0.8;

for(int i=0;i<3;i++)
    row[i]=0;
for(int i=0;i<4;i++)
    column[i]=0;


for (int i=2;i<=21;i++)
{spots=0;

 for (int j=21;j<=62;j++)
    {int white=picture.at<uchar>(i,j);
    white/=255;
    spots+=white;
}
if (spots>42*rate)
{row[0]+=1;

break;}
   
}
 
   
  
for (int i=66;i<=85;i++)
 {spots=0; 

 for (int j=21;j<=62;j++)
   {int white=picture.at<uchar>(i,j);
    white/=255;
    spots+=white;
   }
 if (spots>42*rate)
    {row[1]=1;
    break;
}
   
 }
 
   

for (int i=129;i<=148;i++)
{ spots=0;

 for (int j=21;j<=62;j++)
    {int white=picture.at<uchar>(i,j);
    white/=255;
    spots+=white;
}
if (spots>42*rate)
{row[2]=1;
   break;
}
}
 


/*左上竖线*/
spots=0;
for (int i=0;i<=19;i++)
{
for (int j=25;j<=64;j++)
    {int white=picture.at<uchar>(j,i);
    white/=255;
    spots+=white;
}
}
if (spots>20*40*rate1)
column[0]=1;

/*右上竖线*/ 
spots=0;
for (int i=65;i<=84;i++)
{
 
 for (int j=25;j<=64;j++)
   {int white=picture.at<uchar>(j,i);
    white/=255;
    spots+=white;
   }
 }
if (spots>20*40*rate1)
column[1]=1;
/*左下竖线*/ 
spots=0;
for (int i=0;i<=19;i++)
{
 for (int j=85;j<=124;j++)
    {int white=picture.at<uchar>(j,i);
    white/=255;
    spots+=white;
   }
}
if (spots>20*40*rate1)
column[2]=1;
 /*右下竖线*/ 
spots=0;
for (int i=65;i<=84;i++)
{
 
 for (int j=86;j<=125;j++)
    {int white=picture.at<uchar>(j,i);
    white/=255;
    spots+=white;
}
}
if (spots>20*40*rate1)
column[3]=1;
  


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

