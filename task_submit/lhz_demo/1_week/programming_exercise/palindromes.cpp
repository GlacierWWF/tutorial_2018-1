/***************************************** 
*palindromes.cpp                     
*
*@author    lhz_demo 
*@email     luhzh5@mail2.sysu.edu.cn 
*@version   1.0.0 
*@date      2018/9/26 
*
*Abustract:��swich���б������Ƿ��Ǿ��� 
****************************************/ 

#include<iostream>
#include <cstring>
#include<stdio.h>

using namespace std;

int p,m;
//p��m�����洢�Ƿ���Ļ��߾���
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
        //�����е���������о�

    }
    if(x!=y)
    {
        m=0;
        return;
        //���x��=y��m����0
    }
    else
        m=1;
        //���x==y��m����1
}

int main()
{
    char  a[10000];//����һ���㹻����ַ��������洢������ַ�
    int l;
    cout<<"����������ַ���"<<endl;
    while(scanf("%s",a)==1)
    {
        l=strlen(a);
        //���������ַ��ĳ���
        for(int i=0;i<(l+1)/2;i++)
        {
            if(a[i]!=a[l-1-i])
            {
                p=0;
                break;
                //�жϲ��ǻ��ģ�p=0������ѭ��
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
                  //����һ��δ֪�жϲ��Ǿ�������ѭ��
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
        cout<<"�㻹���Լ��������ַ���"<<endl;

    }
}
