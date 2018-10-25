#include"../inc/Matrix.h"

matrix::matrix()
{
		int i;
		test_matrix.resize(10);
		for(i = 0; i < test_matrix.size(); i++)
				test_matrix[i].resize(pix_row * pix_col);
}

void matrix::test_read()
{
		ifstream inread;
		inread.open("Matrix.txt");
		int length = pix_row * pix_col;
		int i = -1, times = 0;
		char temp;
		if(!inread.is_open())
		{
				cout << " There is no such file." << endl;
				return;
		}
		else
		{
				while(times < pix_row * pix_col *10)
				{
						inread >>  temp;
						if(times % (pix_row*pix_col) == 0)
								i++;
						test_matrix[i][times % (pix_row * pix_col)] = temp - '0';
						times++;
				}
		}
		inread.close();
}

int matrix::compare(vector<vector<int>> &value, int number)
{
		int i, j;
		vector<int> length(10,0);
		for(i =0; i < 10; i++)
				for(j = 0; j < pix_row * pix_col; j++)
						if(value[number][j] != test_matrix[i][j])
								length[i]++;
		int min = 0;
		for(i = 1; i < 10; i++)
				if(length[min] > length[i])
						min = i;

		switch(number)
		{
				case 0:
						cout << "first  ";
						break;
				case 1:
						cout << "second  ";
						break;
				case 2:
						cout << "third  ";
						break;
				case 3:
						cout << "fourth  ";
						break;
		}
		cout << "picture:    ";
		cout << min << endl;
		return min;
}

