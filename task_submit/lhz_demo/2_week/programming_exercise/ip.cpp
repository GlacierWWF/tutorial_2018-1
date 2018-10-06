/***************************************** 
*ip.cpp                     
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/10/6
*
*Abustract: 找到最小的IP和掩码
*****************************************/ 
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

void D2B(int *s,int t)
{
    int i;
    for(i=0;i<8;i++)
    {
        s[i]=t%2;
        t/=2;
    }
}

int main()
{
    int h,i,j,x,sum=0;;
    int  a[10],b[10],ip[4][1000];
    while(scanf("%d",&h)!=EOF)
    {
        for(i=0;i<h;i++)
            scanf("%d.%d.%d.%d",&ip[0][i],&ip[1][i],&ip[2][i],&ip[3][i]);

        for(i=0;i<4;i++)
            sort(ip[i],ip[i]+h);

        for(i=0;i<4;i++)
        {
            int y=ip[i][0];
            if(y!=ip[i][h-1])
                break;
            ip[i][h]=ip[i][0];
            ip[i][h+1]=255;
        }

        D2B(a,ip[i][0]);
        D2B(b,ip[i][h-1]);

        ip[i][h]=0;
        for(x=7;x>=0;x--)
        {
            if(a[x]!=b[x])
            break;
            ip[i][h]=ip[i][h]*2+a[x];
        }
        for(j=x;j>=0;j--)
            ip[i][h]<<=1;
        for(j=i+1;j<4;j++)
            ip[j][h]=0;
        
        for(j=7;j>x;j--)
        {
            sum=sum*2+1;
        }
        for(j=x;j>=0;j--)
            sum=sum*2;
        	ip[i][h+1]=sum;
        for(int t=i+1;t<4;t++)
            ip[t][h+1]=0;

        printf("\n%d.%d.%d.%d\n",ip[0][h],ip[1][h],ip[2][h],ip[3][h]);
        printf("%d.%d.%d.%d\n",ip[0][h+1],ip[1][h+1],ip[2][h+1],ip[3][h+1]);
    }
    return 0;
}

