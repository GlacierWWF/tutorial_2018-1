/**************************************************************************** 
 * @file    Project1.1 队列操作.												*
 * @brief   This file will show how to realize queue manipulate.			*
 * @author	冯颖雯 fengyw8 													*
 * @version	1.0.0															*
 * @date	2018/11/10 														*
 ****************************************************************************/

/// System Headers
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief Queue_Manipulate Main Function
 *------------------------------------------------ 
 * @parameter			void
 *
 * @variable temp		temporary variable
 * @variable a		    queue used to store value 
 *
 * @return 				integer
 */
int main()
{
	int temp;
	queue<int> q;
	//生成随机数并输出、存入 
	srand(time(NULL));
	cout<<"generate random number:"<<endl;
	for(int i=1;i<=10;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		q.push(temp);
	}
	cout<<endl<<endl;
	
	//测试成员函数 
	cout<<"is empty? "<<q.empty()<<endl;
	cout<<"first element of queue:"<<q.front()<<endl;
	cout<<"size of queue:"<<q.size()<<endl;
	cout<<"element of queue:"<<endl;
	while(!q.empty())
	{
		cout<<q.front()<<" ";
		q.pop();
	}
	cout<<endl;
	return 0;
}
