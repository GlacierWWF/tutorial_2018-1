#include<iostream>
#include<stack>

using namespace std;

int main()
{
		//创建堆栈元素
		stack<int> s;
		//元素入栈
		s.push(10);
		s.push(19);
		s.push(23);
		s.push(30);
		s.push(60);

		//元素出栈
		while(!s.empty())
		{
				cout << s.top() << endl;

				s.pop();
		}

		return 0;
}
