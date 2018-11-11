/********************************************************************************
 * @file    Project1.1 map��key����.												*
 * @brief   This file will show how to realize sort in the order of key of map.	*
 * @author	��ӱ�� fengyw8 														*
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
	//������� 
	map<int,int> m;
	
	//��ʼ�� 
	m[1]=2;
	m[0]=3;
	m[100]=12;
	m[50]=10;
	
	//������������������ź��� 
	//iΪiterater��ͨ��iterater������ʵ�ֱ���
	for(auto i=m.begin();i!=m.end();i++) 
		cout<<(*i).first<<" "<<(*i).second<<endl;
		// (*i)Ϊһ��pair��(*i).first��Ӧkey, (*i).second��Ӧvalue 
	//������������map�ڲ�������ǰ���key����� 
	
	return 0;
}
