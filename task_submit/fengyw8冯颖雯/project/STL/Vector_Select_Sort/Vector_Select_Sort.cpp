/**************************************************************************** 
 * @file    Project1.1 vector选择排序.										*
 * @brief   This file will show how to realize select sort using vector.	*
 * @author	冯颖雯 fengyw8 													*
 * @version	1.0.0															*
 * @date	2018/11/10 														*
 ****************************************************************************/

/// System Headers
#include<vector>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

/**
 * @brief user-defined function used to realize select sort 
 *----------------------------------------------------------
 * @parameter       	vector
 *
 * @variable min		minimum value
 * @variable min_index  index of variable min
 *
 * @return				void 
 */
void selectSort(vector<int>& a)
{
	int min,min_index;
	for(int i=0;i<a.size()-1;i++)
	{
		min=a[i];
		min_index=i;
		for(int j=i+1;j<a.size();j++)
			if(min>a[j])
			{
				min=a[j];
				min_index=j;
			}
		a[min_index]=a[i];
		a[i]=min;
	}
	return;
}

/**
 * @brief Vector_Select_Sort Main Function
 *----------------------------------------------
 * @parameter			void
 *
 * @variable temp		temporary variable
 * @variable a		    vector used to store value 
 *
 * @return 				integer
 */
int main()
{
	int temp;
	vector<int> a;
	//生成随机数并输出 
	srand(time(NULL));
	cout<<"generate random number:"<<endl;
	for(int i=1;i<=10;i++)
	{
		temp=rand()%1000;
		cout<<temp<<" ";
		a.push_back(temp);
	}
	cout<<endl<<endl;
	//排序后输出 
	cout<<"after sort:"<<endl;
	selectSort(a);
	for(int i=0;i<a.size();i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0; 
}
