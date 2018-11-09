#include<iostream>
#include<stack>

using namespace std;

/**
 * @brief	Using stack
 *
 * @return integer
 */
int main()
{
	stack<int> stack_i;
	for(int i=0; i<5; i++)
	{
		stack_i.push(i);
		cout << "The number pushed in the stack is: " << i << endl;
		cout << "The size of stack is: " << stack_i.size() << endl;

	}

	cout << "Print the elements of the stack:" << endl;
	while(!stack_i.empty())
	{
		cout << stack_i.top() << " ";
		stack_i.pop();
	}
	cout << endl;

	return 0;

}
