#include<iostream>
#include<queue>
#include<cstdlib>

using namespace std;

int main()
{
		int e, n, m;
		queue<int> q1;

		for(int i = 0; i < 10; i++)
				q1.push(i);
		if (!q1.empty())
				cout << "queue not empty" << endl;

		n = q1.size();
		cout << n << endl;

		m = q1.back();
		cout << m << endl;

		for( int j = 0; j < n; j++)
		{
				e = q1.front();
				cout<<e<<"";
				q1.pop();
		}
		cout << endl;

		if(q1.empty())
				cout << "queue empty" << endl;
		return 0;

}
