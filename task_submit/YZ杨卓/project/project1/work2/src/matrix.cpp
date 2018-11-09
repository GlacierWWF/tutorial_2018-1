/*****************************************
 *  @file    matrix.cpp
 *  @brief   Functions to matrix class
 *
 *---------------------------------------
 *  @Author  杨卓
 *  @Version 1.0.0.1
 *  @Date    11/9/2018
 *----------------------------------------
 */

#include"matrix.h"
#include<iostream>
#include<stdlib.h>
using namespace std;

matrix::matrix()
{
    r = 0;
    c = 0;
    arr = NULL;
}

 matrix::matrix(int m,int n)
{
        r = m;
        c = n;
        arr = new float*[r];
        for(int i=0;i<r;i++)
        arr[i] = new float[c];
}

matrix::matrix(matrix& a)
{
        r = a.r;
        c = a.c;
        arr = new float*[r];
        for(int i=0;i<r;i++)
        arr[i] = new float[c];

        for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
        arr[i][j] = a.arr[i][j];
}


matrix::~matrix()
{
    if(arr != NULL)
    {
        for(int i=0;i<r;i++)
        delete[] arr[i];
        delete[] arr;
    }
}

matrix matrix::operator+(const matrix& a)
{
       if(r!=a.r || c!=a.c)
        {
                cout << "不合法！两个矩阵的行列应该相同 " << endl;
        }
        else
        {

        matrix temp(r,c);
        for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            temp.arr[i][j] = arr[i][j] + a.arr[i][j];
        return temp;

	}
}


matrix matrix::operator-(const matrix& a)
{
    	if(r!=a.r || c!=a.c)
    	{
        	cout << "不合法！两个矩阵的行列应该相同 " << endl;
    	}
    	else
    	{
        	matrix temp(r,c);
        	for(int i=0;i<r;i++)
    	    	for(int j=0;j<c;j++)
       		temp.arr[i][j] = arr[i][j] - a.arr[i][j];
       		return temp;
    	}

}

matrix matrix::operator*(const matrix &a)
{
    matrix temp(r,a.c);
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<a.c;j++)
        {
            float sum=0;
            for(int m=0;m<c;m++)
            {
                sum = sum + arr[i][m] * a.arr[m][j];
            }
        temp.arr[i][j] = sum;
        }
    }
    return temp;
}

matrix& matrix::operator*(float a)
{
    for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
    arr[i][j] = arr[i][j] * a;
    return *this;
}

matrix& matrix::operator=(const matrix& a)
{
   if(this == &a)  return *this;

        r = a.r;
        c = a.c;
        arr = new float*[r];
        for(int i=0;i<r;i++)
        arr[i] = new float[c];

        for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
        arr[i][j] = a.arr[i][j];
        return *this;

}

 float matrix::operator()(int row, int col)
 {
     cout << "Start with (0,0)" << endl;
     if(row>r-1 || col>c-1 || row < 0 || col < 0)     cout << "Invalid! out of range." << endl;
     else       return arr[row][col];
 }

// 重载输出<<
ostream& operator<<(ostream& out, matrix& a)
{
    for(int i=0;i<a.r;i++)
        {
              for(int j=0;j<a.c;j++)
              cout<< a.arr[i][j] << " ";
          cout << endl;
        }
    return out;
}


//重载输入>>
istream& operator>>(istream& in, matrix& a)
{
    for(int i=0;i<a.r;i++)
    for(int j=0;j<a.c;j++)
    cin >> a.arr[i][j];
    return in;
}


// 矩阵元素置零
matrix& matrix::zero()
{
    for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
    arr[i][j] = 0;
    return *this;
}


// 转置
matrix& matrix::transpose()
{
    matrix temp(c, r);
    for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
    {
        temp.arr[j][i] = arr[i][j];
    }
	
    *this = temp;
 
    return *this;
}

// 行访问
void matrix::PrintRow(int row)
{
	while(row >= r || row < 0)
	{
		cout << "Invalid! Rows range from 0 to " << r-1 << endl;
		cout << "Enter row again: ";
		cin >> row;
	}

	for(int j=0; j<c; j++)
		cout << arr[row][j] << " " ;
	cout << endl;
}

// 列访问
void matrix::PrintCol(int col)
{
        while(col >= c || col < 0)
        {

                cout << "Invalid! Cols range from 0 to " << c-1 << endl;
	        cout <<	" Enter col again:  ";
                cin >> col;
        }

	for(int i=0; i<r; i++)
		cout << arr[i][col] << endl;
}


// 点乘
matrix matrix::DotProduct(matrix& a)
{
	matrix temp(r, c);
	for(int i=0; i<r; i++)
		for(int j=0; j<c; j++)
			temp.arr[i][j] = arr[i][j] * a.arr[i][j];
	return temp;	
}

// 矩阵单位化
matrix& matrix::identity()
{
	for(int i=0; i<r; i++)
		for(int j=0; j<c; j++)
			{
				if(i==j)
					arr[i][j] = 1;
				else 
					arr[i][j] = 0;
			}
	return *this;
}


