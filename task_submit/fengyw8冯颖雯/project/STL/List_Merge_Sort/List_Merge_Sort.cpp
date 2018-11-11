/************************************************************************
 * @file    Project1.1 list�鲢����.										*
 * @brief   This file will show how to realize merge sort using list.	*
 * @author	��ӱ�� fengyw8 												*
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
	//������� 
	int temp;
	list<int> a;
	
	//�������������� 
	srand(time(NULL));//���� 
	cout<<"generate random number:"<<endl; 
	for(int i=1;i<=10;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		a.push_back(temp);
	}
	cout<<endl<<endl;
	
	//�������������� 
	cout<<"after sort:"<<endl;
	a.sort();  //���ٶȣ�list�Դ���sort���������ù鲢����ʵ�ֵ� 
	for(auto iterator=a.begin();iterator!=a.end();iterator++)//��������� 
		cout<<*iterator<<" ";
	cout<<endl<<endl;
	
	return 0;
}
