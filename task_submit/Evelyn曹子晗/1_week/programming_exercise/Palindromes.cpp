#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

//bool isLegal(char *p);
bool contains(char *p, char c);
bool isMirror(char *p);
bool isPalin(char *p);
int main()
{
	cout << "Please input several lines of strings composed of NO MORE THAN 20 capital letters in a line:" ;
	cout << "(Please press ENTER again to check the result when all is entered.)" << endl;
	
	char c[100][21];   //Contain 100 rows at most.
	re: int i = 0;
	while (i < 100 )
	{

		cin.getline(c[i],21);
			
//Judge whether there is illegal letter or not
//			if(!isLegal(c[i]))
//			{
//				cout << "Contain ILLEGAL letter! Please input again!" << endl;
//				goto re;
//			}

			if(strlen(c[i]) == 0)
			{
				break;
			}
			i++;
	}

	for (int k=0; k<i; k++)
	{
		if(!isMirror(c[k]))
		{
			if(!isPalin(c[k]))
				cout << c[k] << " -- is not a palindrome.\n\n";
			else
				cout << c[k] << " -- is a regular palindrome.\n\n";
		}
		else
		{
			if(!isPalin(c[k]))
				cout << c[k] << " -- is a mirrored string.\n\n";
			else
				cout << c[k] << " -- is a mirrored palindrome.\n\n";
		}
	}
	system("pause");
	return 0;
}

//Judge whether the input strings is legal or not
//bool isLegal(char *p)
//{
//	for ( ; *p != '\0'; p++)
//	{
//		if(!(*p >= 'A' && *p <= 'Z' || *p >= '1' && *p == '9'))
//		{
//			return false;
//	    }
//	}
//	return true;
//}

//Judge whether the specific letter is contained or not
bool contains(char *p, char c)
{
	while( *p != '\0')
	{
		if (*p == c)
		{
			return true;
		}
		p++;
	}
	return false;
}

//Judge whether the string is mirrored or not
bool isMirror(char *p)
{
	bool isMirror = true;
	char c1[20] = {'B', 'C', 'D', 'F', 'G', 'K', 'N', 'P', 'Q', 'R', '4', '6', '7', '9'};
	char c2[20] = {'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y', '1', '8'};
	char c3[10] = {'E', '3', 'L', 'J', 'S', '2', 'Z', '5'};
	char *r = p;
	while(*r != '\0')
	{
		if(contains(c1, *r))
		{
		    return false;
		}
		r++;
	}
		char *q = p;
		while(*q != '\0')
			{
				q++;
			}
			q--;
			while(p <= q)
			{
				if (p == q && !contains(c2, *p))
				{
					isMirror = false;
				}
				if (contains(c2, *p) && *p != *q)
				{
					isMirror = false;
				}
				if (contains(c3, *p))
				{
					if(*p == 'E' && *q != '3' || *p == '3' && *q != 'E')
						isMirror = false;
					if(*p == 'L' && *q != 'J' || *p == 'J' && *q != 'L')
						isMirror = false;
					if(*p == 'S' && *q != '2' || *p == '2' && *q != 'S')
						isMirror = false;
				    if(*p == 'Z' && *q != '5' || *p == '5' && *q != 'Z')
						isMirror = false;
				}
				p++;
				q--;
			}
		
	return isMirror;
}

bool isPalin(char *p)
{
	char *q = p;
	while(*q != '\0')
	{
		q++;
	}
	q--;
	while(p < q)
	{
		if (*p != *q)
		{
			return false;
		}
		p++;
		q--;
	}
	return true;
}
