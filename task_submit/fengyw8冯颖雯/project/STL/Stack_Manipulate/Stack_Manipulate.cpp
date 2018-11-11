/**************************************************************************** 
 * @file    Project1.1 栈操作.												*
 * @brief   This file will show how to realize stack manipulate.			*
 * @author	冯颖雯 fengyw8 													*
 * @version	1.0.0															*
 * @date	2018/11/10 														*
 ****************************************************************************/

/// System Headers
#include<iostream>
#include<stack>
#include<cstdlib>
#include<ctime>

using namespace std;

/**
 * @brief Stack_Manipulate Main Function
 *------------------------------------------------ 
 * @parameter			void
 *
 * @variable temp		temporary variable
 * @variable s		    stack used to store value 
 *
 * @return 				integer
 */
int main()
{
	int temp;
	stack<int> s;
	//生成随机数 
	srand(time(NULL));
	cout<<"generate random number:"<<endl;
	for(int i=1;i<=10;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		s.push(temp);
	}
	cout<<endl<<endl; 
	//测试成员函数
	cout<<"is empty? "<<s.empty()<<endl;
	cout<<"top element of stack:"<<s.top()<<endl;
	cout<<"size of stack:"<<s.size()<<endl;
	cout<<"element of stack:"<<endl;
	while(!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}
	cout<<endl;
	return 0;
} 
