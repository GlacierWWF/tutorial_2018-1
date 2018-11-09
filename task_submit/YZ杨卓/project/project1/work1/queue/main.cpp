#include<iostream>
#include<queue>

using namespace std;

/**
 * @brief	Code for using queue
 *
 * @return	integer
 */

int main()
{
	queue<int> ique;
	        for(int i=0; i<5; i++)
        {
                ique.push(i);
                cout << "The number added to the queue is: " << i << endl;
                cout << "The size of queue is: " << ique.size() << endl;

        }

        cout << "Print the elements of the queue:" << endl;
        while(!ique.empty())
        {
                cout << ique.front() << " ";
                ique.pop();
        }
        cout << endl;


	return 0;
}
