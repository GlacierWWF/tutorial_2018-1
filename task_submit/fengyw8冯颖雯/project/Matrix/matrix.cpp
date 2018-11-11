#include"matrix.hpp"
#include<iostream>
#include<vector>
using namespace std;
matrix::matrix()
{
	row=col=0;
	data=NULL;
	return;
}
matrix::matrix(int r,int c)
{
	if(r<=0 || c<=0)
	{
		row=col=0;
		data=NULL;
		return;
	}
	row=r;
	col=c;
	data=new int*[row];
	for(int i=0;i<=row-1;i++)
	{
		data[i]=new int[col];
		for(int j=0;j<=col-1;j++)
			data[i][j]=0;
	}
	return;
}
matrix::matrix(vector<vector<int>>& arr)
{
	row=arr.size();
	col=arr[0].size();
	data=new int*[row];
	for(int i=0;i<=row-1;i++)
	{
		data[i]=new int[col];
		for(int j=0;j<=col-1;j++)
			data[i][j]=arr[i][j];
	}
	return;
}
matrix::matrix(const matrix& other)
{
	row=other.row;
	col=other.col;
	data=new int*[row];
	for(int i=0;i<=row-1;i++)
	{
		data[i]=new int[col];
		for(int j=0;j<=col-1;j++)
			data[i][j]=other.data[i][j];
	}
	return;
}
matrix::~matrix()
{
	for(int i=0;i<row-1;i++)
		delete[] data[i];
	delete[] data;
	return;
}
matrix& matrix::operator=(const matrix& other)
{
	for(int i=0;i<row-1;i++)
		delete[] data[i];
	delete[] data;
	row=other.row;
	col=other.col;
	data=new int*[row];
	for(int i=0;i<=row-1;i++)
	{
		data[i]=new int[col];
		for(int j=0;j<=col-1;j++)
			data[i][j]=other.data[i][j];
	}
	return *this;
}
matrix matrix::operator+(const matrix& right) const
{
	if(!(row==right.row && col==right.col))
	{
		cout<<"wrong! The two matrices to be added are not matched!"<<endl;
		return matrix();
	}
	matrix temp=*this;
	for(int i=0;i<=row-1;i++)
		for(int j=0;j<=col-1;j++)
			temp.data[i][j]+=right.data[i][j];
	return temp;
}
matrix matrix::operator-(const matrix& right) const
{
	if(!(row==right.row && col==right.col))
	{
		cout<<"wrong! The two matrices to be subtracted are not matched!"<<endl;
		return matrix();
	}
	matrix temp=*this;
	for(int i=0;i<=row-1;i++)
		for(int j=0;j<=col-1;j++)
			temp.data[i][j]-=right.data[i][j];
	return temp;
}
matrix matrix::operator*(const int right) const
{
	matrix temp=*this;
	for(int i=0;i<=row-1;i++)
		for(int j=0;j<=col-1;j++)
			temp.data[i][j]*=right;
	return temp;
}
matrix operator*(const int num,const matrix& m)
{
	return m*num;
}
matrix matrix::operator*(const matrix& right) const
{
	if(col!=right.row)
	{
		cout<<"wrong! The two matrices to be multiplied are not matched!"<<endl;
		return matrix();
	}
	matrix temp(row,right.col);
	for(int i=0;i<=temp.row-1;i++)
		for(int j=0;j<=temp.col-1;j++)
			for(int k=0;k<=right.row-1;k++)
				temp.data[i][j]+=data[i][k]*right.data[k][j];
	return temp;
}
matrix matrix::transpose() const
{
	matrix temp(col,row);
	for(int i=0;i<=row-1;i++)
		for(int j=0;j<=col-1;j++)
			temp.data[j][i]=data[i][j];
	return temp;
}
void matrix::printRow(int r) const
{
	if(r<0 || r>=row)
	{
		cout<<"Wrong row index!"<<endl;
		return;
	}
	for(int i=0;i<=col-1;i++)
		cout<<data[r][i]<<" ";
	cout<<endl;
	return;
}
void matrix::printCol(int c) const 
{
	if(c<0 || c>=col)
	{
		cout<<"Wrong column index!"<<endl;
		return;
	}
	for(int i=0;i<=row-1;i++)
		cout<<data[i][c]<<" ";
	cout<<endl;
	return;
}
void matrix::setZero()
{
	for(int i=0;i<=row-1;i++)
		for(int j=0;j<=col-1;j++)
			data[i][j]=0;
	return;
}
matrix matrix::setIdentity(int n)
{
	matrix temp(n,n);
	for(int i=0;i<=n-1;i++)
		temp.data[i][i]=1;
	return temp;
}
istream& operator>>(istream& in,matrix& right)
{
	for(int i=0;i<=right.row-1;i++)
		for(int j=0;j<=right.col-1;j++)
			cin>>right.data[i][j];
	return in;
}
ostream& operator<<(ostream& out,matrix& right)
{
	for(int i=0;i<=right.row-1;i++)
		right.printRow(i);
	return out;
}
int& matrix::operator()(int r,int c)
{
	if(r<0 || r>=row || c<0 || c>=col)
	{
		cout<<"Wrong entry index!"<<endl;
		return data[0][0];
	}
	return data[r][c];
}
int matrix::operator()(int r,int c) const
{
	if(r<0 || r>=row || c<0 || c>=col)
	{
		cout<<"Wrong entry index!"<<endl;
		return data[0][0];
	}
	return data[r][c];
}
int matrix::getRow() const
{
	return row;
}
int matrix::getCol() const
{
	return col;
}
