/*****************************************
 *  @file    main.cpp
 *  @brief   test program for function sort
 *
 *---------------------------------------
 *  @Author  杨卓
 *  @Version 1.0.0.1
 *  @Date    11/9/2018
 *----------------------------------------
 */

#include "MySort.cpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 用户提供的比较string的函数
bool mycmps(string s1, string s2)
{
	return s1 > s2;
}

// 用户提供的比较int的函数
bool mycmpi(int a, int b)
{
	return a > b;
}


/**
 * @brief	test code for function sort
 *
 * @return	integer
 */

int main()
{
	vector<string> v;

	v.push_back("bc");
	v.push_back("abc");
	v.push_back("a");

	// 使用迭代器
	cout << "before vector<string> sort: " << endl;
	for(int i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;

	
	MySort(v.begin(), v.end());

	cout << "after vector<string> sort: " << endl;
	for(int i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;

   	MySort(v.begin(), v.end(), mycmps);
   
   	cout << "Use user-defined comparison functions: " << endl;
        for(int i=0; i<v.size(); i++)
                cout << v[i] << " ";
	cout << endl;
	
	// 传入简单c数组
	char ch[10] = {'d','a', 'c', 'b'};
	cout << "传入简单c数组 " << endl << "before sort : " << endl;
	for(int i=0;i<4;i++)
	cout << ch[i] << " ";
	cout << endl;
	
	MySort(ch, 0, 3, mycmpi);
	
	cout << "after sort （使用用户提供的比较函数）: " << endl;
	for(int i=0;i<4;i++)
	cout << ch[i] << " ";
	cout << endl;


	int arr[10] = {9,4,1,6};
        cout << "before sort: " << endl;
	for(int i=0;i<4;i++)
        cout << arr[i] << " ";
        cout << endl;

        MySort(arr, 0, 3);

	cout << "after sort (使用默认比较函数) " << endl;
        for(int i=0;i<4;i++)
        cout << arr[i] << " ";
        cout << endl;



	return 0;
}
