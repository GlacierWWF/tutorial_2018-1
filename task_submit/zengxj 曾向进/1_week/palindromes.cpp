/*Title Here: Palindromes
- Author: 曾向进 
-Revised: 曾向进 
- Date: 2018-09-29 
- Version: 1.0.0
Functions: 判断字符是否回文或镜像对称 
Depend Libraries:isostream、string.h 
*/


#include <iostream> 
#include <string.h>
using namespace std;

int ishuiwen(char *p)
{
	int len = strlen(p);
	int flag1 = 1;
	for (int i = 0; i<len / 2; ++i)
	{
		if (p[i] != p[len - i - 1])
		{
			flag1 = 0;
			break;
		}
	}
	return flag1;
}
int ismirror(char *p)
{
	int len = strlen(p);
	int flag2 = 1;
	for (int i = 0; i < len; i++)
	{
		if (p[i] == 'B' || p[i] == 'C' || p[i] == 'F' || p[i] == 'G' || p[i] == 'K' || p[i] == 'N' || p[i] == 'P' || p[i] == 'Q' || p[i] == 'R' || p[i] == '4' || p[i] == '6' || p[i] == '7' || p[i] == '9' || p[i] == 'D')
		{
			   flag2 = 0;
			   return flag2;
		}
	}
	for (int i = 0; i<len / 2; ++i)
	{
		if (p[i] == 'A' || p[i] == 'H' || p[i] == 'I' || p[i] == 'M' || p[i] == 'O' || p[i] == 'T' || p[i] == 'V' || p[i] == 'U' || p[i] == 'W' || p[i] == 'X' || p[i] == 'Y' || p[i] == '1' || p[i] == '8')
		{
			if (p[i] != p[len - i - 1])
			{
				flag2 = 0;
				break;
			}
		}
		else 
		{
			if (p[i] == 'E')
			{
				if (p[len - i - 1] != '3')
				{
					flag2 = 0;
					break;
				}
			}

			if (p[i] == 'L')
			{
				if (p[len - i - 1] != 'J')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == 'J')
			{
				if (p[len - i - 1] != 'L')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == 'Z')
			{
				if (p[len - i - 1] != '5')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == '5')
			{
				if (p[len - i - 1] != 'Z')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == 'S')
			{
				if (p[len - i - 1] != '2')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == '2')
			{
				if (p[len - i - 1] != 'S')
				{
					flag2 = 0;
					break;
				}
			}
			
			if (p[i] == '3')
			{
				if (p[len - i - 1] != 'E')
				{
					flag2 = 0;
					break;
				}
			}
			 
		
		}
	}
	return flag2;
}

int main()
{char p[100];
	while (cin>>p)
	{
		int pali;
		int mir;
		pali = ishuiwen(p);
		mir = ismirror(p);
		
		if (pali == 1 && mir == 1)
		{
			cout << p << " -- is a mirrored palindrome." << endl;
		}
		else if (pali == 1)
			cout << p << " -- is a regular palindrome." << endl;
		else if (mir == 1)
			cout << p << " -- is a mirrored string." << endl;
		else
		{
			cout << p << " --is not a palindrome." << endl;
		}
	}
	
	return 0;
}
