#include"matrix.hpp"
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<vector<int>> array1={{1,2},{3,4},{5,6}};
	vector<vector<int>> array2={{6,5},{4,3},{2,1}};
	vector<vector<int>> array3={{1,2,3},{4,5,6}};
	matrix m1(array1);
	matrix m2(array2);
	matrix m3(array3);
	
	//打印三个矩阵 
	cout<<"Matrix1:"<<endl
		<<m1<<endl
		<<"Matrix2:"<<endl
		<<m2<<endl
		<<"Matrix3:"<<endl
		<<m3<<endl;
	
	//测试矩阵运算 
	matrix 	t1=m1+m2,
			t2=m1-m2,
			t3=4*m1,
			t4=m1*m3,
			t5=m1.transpose();
	cout<<"Matrix1 + Matrix2:"<<endl
		<<t1<<endl
		<<"Matrix1 - Matrix2:"<<endl
		<<t2<<endl
		<<"4 * Matrix1:"<<endl
		<<t3<<endl
		<<"Matrix1 * Matrix3:"<<endl
		<<t4<<endl
		<<"Transpose of Matrix1:"<<endl
		<<t5<<endl; 
	
	//测试行访问、列访问和置零 
	cout<<"The 2nd row of Matrix1:"<<endl;
	m1.printRow(1);
	cout<<"The 2nd column of Matrix1:"<<endl;
	m1.printCol(1);
	cout<<"Set matrix1 to zero matrix:"<<endl;
	m1.setZero();
	cout<<m1<<endl;
	
	//测试修改单个矩阵元素 
	cout<<"Modify the entry of matrix1 at (0,0) and (1,1) to 3 and 10:"<<endl;
	m1(0,0)=3;
	m1(1,1)=10;
	cout<<m1<<endl;
	
	//测试输出单位矩阵及矩阵行列数 
	matrix t6=matrix::setIdentity(5);
	cout<<"Identity matrix of 5:"<<endl
		<<t6<<endl
		<<"The rows of Matrix1:"<<endl
		<<m1.getRow()<<endl
		<<"The columns of Matrix2:"<<endl
		<<m1.getCol()<<endl;
	return 0;
}
