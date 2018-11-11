#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<vector>
using namespace std;
class matrix
{
public:
	//构造一个空的矩阵
	matrix();
	//构造一个指定了行和列的矩阵，并初始化为0 
	matrix(int r,int c);
	//用二维数组初始化矩阵
	matrix(vector<vector<int>>& arr);
	//拷贝构造函数 
	matrix(const matrix& other);
	//析构函数 
	~matrix();
	//重载赋值运算符 
	matrix& operator=(const matrix& other);
	//重载加号 
	matrix operator+(const matrix& right) const;
	//重载减号
	matrix operator-(const matrix& right) const;
	
	//重载乘号运算符
	//数乘 
	matrix operator*(const int right) const;
	friend matrix operator*(const int num,const matrix& m);
	//矩阵乘法
	matrix operator*(const matrix& right) const;
	
	//返回转置矩阵 
	matrix transpose() const;
	//行访问
	void printRow(int r) const;
	//列访问
	void printCol(int c) const;
	//设为0矩阵
	void setZero();
	//返回单位矩阵
	static matrix setIdentity(int n);
	//输入输出 
	friend istream& operator>>(istream& in,matrix& right);
	friend ostream& operator<<(ostream& out,matrix& right);
	//访问单个元素
	int& operator()(int r,int c);
	int operator()(int r,int c) const;
	//得到行数和列数信息
	int getRow() const;
	int getCol() const;
private:
	int** data;
	int row;
	int col;
};
#endif
