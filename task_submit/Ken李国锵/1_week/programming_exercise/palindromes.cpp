//Palindromes & Mirrored Strings Identifier :)
//BY:Ken李国锵

#include <iostream>
#include <string>

using namespace std;

const string mirror = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const string ans[] = { "not a palindrome", "a regular palindrome", "a mirrored string", "a mirrored palindrome" };

//定义检测函数r
char R(char ch)
{
		if (isalpha(ch))
				return mirror[ch - 'A'];
		else
				return mirror[ch - '0' + 25];
}

int main ()
{
		string s;
		//检测输入区
		while (cin>>s)
		{
				bool Mirror = true;
				bool Palindrome = true;
				for (int i = 0; i < s.size() / 2 + 1; i++)
				{
						if (s[i] != s[s.size() - i - 1])
								Mirror = false;
						if (s[i] != R(s[s.size() - i - 1])) 
								Palindrome = false;
				}
				//判断输出区
				cout << s << " -- is ";
				if (Mirror && Palindrome)
						cout << ans[3];
				else if (Mirror && !Palindrome)
						cout << ans[2];
				else if (!Mirror && Palindrome)
						cout << ans[1];
				else
						cout << ans[0];
				cout << endl;
		}
}



				  
