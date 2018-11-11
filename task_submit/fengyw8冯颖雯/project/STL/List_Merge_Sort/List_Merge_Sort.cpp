/************************************************************************
 * @file    Project1.1 list归并排序.										*
 * @brief   This file will show how to realize merge sort using list.	*
 * @author	冯颖雯 fengyw8 												*
 * @version	1.0.0														*
 * @date	2018/11/10 													*
 ************************************************************************/ 

/// System Headers
#include<list>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
 
/**
 * @brief List_Merge_Sort Main Function
 *------------------------------------------------
 * @parameter			void
 *
 * @variable temp		temporary variable
 * @variable a		    list used to store value 
 *
 * @return 				integer
 */
int main()
{
	//定义变量 
	int temp;
	list<int> a;
	
	//生成随机数并输出 
	srand(time(NULL));//种子 
	cout<<"generate random number:"<<endl; 
	for(int i=1;i<=10;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		a.push_back(temp);
	}
	cout<<endl<<endl;
	
	//将随机数排序并输出 
	cout<<"after sort:"<<endl;
	a.sort();  //经百度，list自带的sort函数就是用归并排序实现的 
	for(auto iterator=a.begin();iterator!=a.end();iterator++)//遍历并输出 
		cout<<*iterator<<" ";
	cout<<endl<<endl;
	
	return 0;
}
