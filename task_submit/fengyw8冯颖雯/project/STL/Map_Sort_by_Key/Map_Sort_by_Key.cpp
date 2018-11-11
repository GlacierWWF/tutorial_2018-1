/********************************************************************************
 * @file    Project1.1 map按key排序.												*
 * @brief   This file will show how to realize sort in the order of key of map.	*
 * @author	冯颖雯 fengyw8 														*
 * @version	1.0.0																*
 * @date	2018/11/10 															*
 ********************************************************************************/

/// System Headers
#include<map>
#include<iostream>
#include<string>

using namespace std;

/**
 * @brief Map_Sort_by_Key Main Function
 *---------------------------------------------------
 * @parameter		void
 *
 * @variable m		map used to store key and value
 *
 * @return			integer
 */
int main()
{
	//定义变量 
	map<int,int> m;
	
	//初始化 
	m[1]=2;
	m[0]=3;
	m[100]=12;
	m[50]=10;
	
	//遍历并输出（本身已排好序） 
	//i为iterater，通过iterater自增来实现遍历
	for(auto i=m.begin();i!=m.end();i++) 
		cout<<(*i).first<<" "<<(*i).second<<endl;
		// (*i)为一个pair，(*i).first对应key, (*i).second对应value 
	//输出结果表明，map内部本身就是按照key排序的 
	
	return 0;
}
