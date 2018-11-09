/*****************************************
 *  @file    main.cpp
 *  @brief   program to matrix class
 *
 *---------------------------------------
 *  @Author  杨卓
 *  @Version 1.0.0.1
 *  @Date    11/9/2018
 *----------------------------------------
 */

#include<iostream>
#include"matrix.h"

using namespace std;

matrix& CreateMatrix(matrix& m);


int main()
{
	matrix m, m1, m2;
	matrix res;
/*
	// 加法
	cout << "Add test: " << endl;
	cout << "Matrix1: " << endl;
	CreateMatrix(m1);

	cout << "Matrix2: " << endl;
 	CreateMatrix(m2);

	res = m1 + m2;
	cout << "Result: " << endl;
	cout << res << endl << endl;
	
	// 减法
        cout << "Subtraction test: " << endl;
        cout << "Matrix1: " << endl;
       	CreateMatrix(m1);

        cout << "Matrix2: " << endl;
        CreateMatrix(m2);

	res = m1 - m2;
	cout << "Result: " << endl;
        cout << res << endl << endl;

	// 叉乘
	cout << "Matrix multiplication cross: " << endl;
        cout << "Matrix1: " << endl;
        CreateMatrix(m1);

        cout << "Matrix2: " << endl;
        CreateMatrix(m2);

	res = m1 * m2;
        cout << "Result: " << endl;
        cout << res << endl << endl;
	
	//数乘
        cout << "数乘 test: " << endl;
        cout << "Matrix: " << endl;
        CreateMatrix(m);

	float num;
	cout << "Enter the number you want to multiply the matrix with: " ;
	cin >> num;

	res = m * num;
	cout << "Result: " << endl;
        cout << res << endl << endl;

	//点乘
        cout << "Matrix Dot Product: " << endl;
        cout << "Matrix1: " << endl;
        CreateMatrix(m1);

        cout << "Matrix2: " << endl;
        CreateMatrix(m2);

        res = m1.DotProduct(m2);
        cout << "Result: " << endl;
        cout << res << endl << endl;

	//矩阵置零
	cout << "Zero test: " << endl;
	CreateMatrix(m);
	m.zero();
	cout << "Zero() result: " << endl;
	cout << m << endl;

	//行访问
	cout << "PrintRow test: " << endl;
	int row;
	CreateMatrix(m);
	cout << "Enter the row: " << endl;
	cin >> row;
	cout << "Result: " << endl;
	m.PrintRow(row);
	cout << endl;

	//列访问
	cout << "PrintCol test: " << endl;
        int col;
        CreateMatrix(m);
        cout << "Enter the col: " << endl;
        cin >> col;
        cout << "Result: " << endl;
        m.PrintCol(col);
        cout << endl;

	//转置
	cout << "transpose test: " << endl;
	CreateMatrix(m);
	m.transpose();
	cout << "Result:" << endl << m << endl;
*/
	
	//单位矩阵
	cout << "identity() test: " << endl;
	CreateMatrix(m);
	if(m.getr() != m.getc())
		cout << "Invalid! Rows and columns must be equal! " << endl;
	else
	{
		m.identity();
		cout << "Result: " << endl << m << endl << endl;
	}
	return 0;
}

/**
 * @brief	create a matrix
 *
 * @param	matrix reference
 * 
 * @return	matrix reference
 *
 */
matrix& CreateMatrix(matrix& m)
{
        int r, c;
        cout  <<  "Enter rows and columns: " << endl;
        cin >> r >> c ;
	
 	matrix temp(r, c);
	cout << "Enter the elements: " << endl;
	cin >> temp;

	m = temp;

	return m;

}


