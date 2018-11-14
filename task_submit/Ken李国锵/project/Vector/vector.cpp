#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct example
{
		int elem1;
		int elem2;
}example;

bool comparison(example a, example b)
{
		return a.elem1<b.elem1;
}

int main()
{
		int N;
		cin >> N;

		vector<example> array(N);

		for(int i=0; i<N; i++)
		{
				cin >> array[i].elem1 >> array[i].elem2;
		}

		sort(array.begin(), array.end(), comparison);

		for(int i=0; i<N; i++)
		{
				cout << array[i].elem1 << " " << array[i].elem2 << endl;
		}
		return 0;
}

