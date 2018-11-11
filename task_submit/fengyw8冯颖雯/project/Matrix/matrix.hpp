#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<vector>
using namespace std;
class matrix
{
public:
	//����һ���յľ���
	matrix();
	//����һ��ָ�����к��еľ��󣬲���ʼ��Ϊ0 
	matrix(int r,int c);
	//�ö�ά�����ʼ������
	matrix(vector<vector<int>>& arr);
	//�������캯�� 
	matrix(const matrix& other);
	//�������� 
	~matrix();
	//���ظ�ֵ����� 
	matrix& operator=(const matrix& other);
	//���ؼӺ� 
	matrix operator+(const matrix& right) const;
	//���ؼ���
	matrix operator-(const matrix& right) const;
	
	//���س˺������
	//���� 
	matrix operator*(const int right) const;
	friend matrix operator*(const int num,const matrix& m);
	//����˷�
	matrix operator*(const matrix& right) const;
	
	//����ת�þ��� 
	matrix transpose() const;
	//�з���
	void printRow(int r) const;
	//�з���
	void printCol(int c) const;
	//��Ϊ0����
	void setZero();
	//���ص�λ����
	static matrix setIdentity(int n);
	//������� 
	friend istream& operator>>(istream& in,matrix& right);
	friend ostream& operator<<(ostream& out,matrix& right);
	//���ʵ���Ԫ��
	int& operator()(int r,int c);
	int operator()(int r,int c) const;
	//�õ�������������Ϣ
	int getRow() const;
	int getCol() const;
private:
	int** data;
	int row;
	int col;
};
#endif
