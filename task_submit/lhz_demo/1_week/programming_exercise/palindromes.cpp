/***************************************** 
*palindromes.cpp                     
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/9/26 
*
*Abustract:用swich来判别输入是否是镜像串 
****************************************/ 

#include<iostream>
#include <cstring>
#include<stdio.h>

using namespace std;

int p,m;
//p和m用来存储是否回文或者镜像
void mirchar(char x,char y)
{
    switch(x)
    {
        case'A': x='A';break;
        case'E': x='3';break;
        case'H': x='H';break;
        case'I': x='I';break;
        case'J': x='L';break;
        case'L': x='J';break;
        case'M': x='M';break;
        case'O': x='O';break;
        case'S': x='2';break;
        case'T': x='T';break;
        case'U': x='U';break;
        case'V': x='V';break;
        case'W': x='W';break;
        case'X': x='X';break;
        case'Y': x='Y';break;
        case'Z': x='5';break;
        case'1': x='1';break;
        case'2': x='S';break;
        case'3': x='E';break;
        case'5': x='Z';break;
        case'8': x='8';break;
        default:  x=' ';break;
        //把所有的情况意义列举

    }
    if(x!=y)
    {
        m=0;
        return;
        //如果x！=y，m记作0
    }
    else
        m=1;
        //如果x==y，m记作1
}

int main()
{
    char  a[10000];//定义一个足够大的字符数组来存储输入的字符
    int l;
    cout<<"请输入检测的字符串"<<endl;
    while(scanf("%s",a)==1)
    {
        l=strlen(a);
        //计算输入字符的长度
        for(int i=0;i<(l+1)/2;i++)
        {
            if(a[i]!=a[l-1-i])
            {
                p=0;
                break;
                //判断不是回文，p=0，跳出循环
            }
            else
                p=1;

        }
        for(int i=0;i<(l+1)/2;i++)
        {
            mirchar(a[i],a[l-1-i]);
            if(m==0)
            {
                  break;
                  //当有一个未知判断不是镜像，跳出循环
            }
        }
        if(p==1&&m==1)
            cout<<a<<" -- is a mirrored palindrome."<<endl<<endl;
        else if(m==1)
            cout<<a<<"-- is a mirrored string."<<endl<<endl;
        else if(p==1)
            cout<<a<<"-- is a regular palindrome."<<endl<<endl;
        else
            cout<<a<<"-- is not a palindrome."<<endl<<endl;
        cout<<"你还可以继续输入字符串"<<endl;

    }
}
