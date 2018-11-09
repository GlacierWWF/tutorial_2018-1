/*****************************************
 *  @file    MySort.cpp
 *  @brief   code for function MySort()
 *
 *---------------------------------------
 *  @Author  杨卓
 *  @Version 1.0.0.1
 *  @Date    11/9/2018
 *----------------------------------------
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*********************************************
 * 默认的比较函数（升序）
 */
template< typename T>
bool MyCmp(T t1, T t2)
{
	return t1 < t2;
}

// 传入参数为string时的比较函数
template< >
bool MyCmp(string s1, string s2)
{
	int sum1 = 0, sum2 = 0;
	for(int i=0; i<s1.length(); i++)
		sum1 += int(s1[i]);

        for(int i=0; i<s2.length(); i++)
		sum2 += int(s2[i]);

	return sum1 < sum2;
}


//*********************************************
// MySort 的四种重载形式，对应不同的输入参数

//传入参数为迭代器时
template< typename T, typename CMP>
void MySort(T t1, T t2, CMP cmp)
{
	if(t1 == t2)   return ;
	for(; t1 != t2; --t2)
		for(T temp = t1+1; temp != t2; ++temp)
			if( cmp(*temp, *(temp-1)) )
				swap(*temp, *(temp-1));
}


template< typename T>
void MySort(T t1, T t2)
{
	if(t1 == t2)	return ;
	for(; t1 != t2; --t2)
		for(T temp = t1+1; temp != t2; ++temp)
			if( MyCmp(*temp, *(temp-1)) )
				swap(*temp, *(temp-1));
}

//传入参数为普通c数组时
template< typename T, int size >
void MySort(T (&arr)[size], int a, int b)
{
	for(int i=a; i<=b; i++)
		for(int j=i+1; j<=b; j++)
			if( MyCmp(arr[j], arr[i]) )
				swap(arr[j], arr[i]);
}


template< typename T, int size, typename CMP >
void MySort(T (&arr)[size], int a, int b, CMP cmp)
{
        for(int i=a; i<=b; i++)
                for(int j=i+1; j<=b; j++)
                        if( cmp(arr[j], arr[i]) )
                                swap(arr[j], arr[i]);
}
