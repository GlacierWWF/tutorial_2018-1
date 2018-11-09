#ifndef MATRIX_H_
#define MATRIX_H_
#include"iostream"
using namespace std;


class matrix
{

private:
    int r;
    int c;
    float **arr;

public:

    // 缺省构造函数
    matrix();

    // 带参数的构造函数
    matrix(int m,int n);

    // 拷贝构造函数
    matrix(matrix& a);

    // 析构函数
    ~matrix();

    int getr()  {return r;}
    
    int getc()  {return c;}

    // 重载加法
    matrix operator+(const matrix& a);

    // 重载减法
    matrix operator-(const matrix& a);

    // 重载矩阵叉乘
    matrix operator*(const matrix& a);

    // 重载矩阵数乘
    matrix& operator*(float a);

    // 重载= (深复制)
    matrix& operator=(const matrix& a);

    // 取矩阵元素()
    float operator()(int row, int col);

    // 重载 <<
    friend ostream& operator<<(ostream& out, matrix& a);

    // 重载 >>
    friend istream& operator>>(istream& in, matrix& a);

    // 矩阵置零
    matrix& zero();	

    // 转置
    matrix& transpose();

    // 行访问
    void PrintRow(int row);

    // 列访问
    void PrintCol(int col);

    // 矩阵点乘
    matrix DotProduct(matrix& a);
 
    //单位矩阵
    matrix& identity();

};

#endif
