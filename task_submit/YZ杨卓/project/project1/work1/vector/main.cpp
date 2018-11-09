#include<iostream>
#include<vector>

using namespace std;

void selectSort(vector<int>& vec);
int findMin(vector<int> vec, int i);

/**
 * @brief	Selection sort for vector
 *
 * @return	integer
 */

int main()
{	
	vector<int> vec;
	int data;
	
	cout << "Please enter the numbers (Enter 'enter' to end the input)" << endl;
	while(1)
	{
		cin >> data;
		vec.push_back(data);
		if(cin.get() == '\n')
			break;
	}
	
	selectSort(vec);
	
	for(int i=0; i<vec.size(); i++)
		cout << vec[i] << " " ;
	
	
	cout << endl;

	return 0;
}

/**
 * @brief	Selection sort for vector
 *
 * @param	vector that you want to sort
 */

void selectSort(vector<int>& vec)
{ 
	int i;
	int min_pos = 0;
	for(i=0; i<vec.size(); i++)
	{
		min_pos = findMin(vec, i);
		swap(vec[i], vec[min_pos]);
	}
}

/**
 * @brief
 *
 * @param1	vector you want to sort
 * @param2	Current vector position
 *
 * @return	Minimum number position
 */ 
int findMin(vector<int> vec, int i)
{
	int pos = i;
	for(int j=i+1; j<vec.size(); j++)
	{
		if(vec[pos] > vec[j])
			pos = j;
	}

	return pos;
}


