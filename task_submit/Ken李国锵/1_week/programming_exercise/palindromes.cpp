#include <iostream>
#include <string>

using namespace std;

const string mirror = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const string ans[] = { "not a palindrome", "a regular palindrome", "a mirrored string", "a mirrored palindrome" };

char r(char ch)
{
		if (isalpha(ch))
				return mirror[ch - 'A'];
		else
				return mirror[ch - '0' + 25];
}

int main ()
{
		string s;
		while (cin>>s)
		{
				bool isMirror = true;
				bool isPalindrome = true;
				for (int i = 0; i < s.size() / 2 + 1; i++)
				{
						if (s[i] != s[s.size() - i - 1])
								isMirror = false;
						if (s[i] != r(s[s.size() - i - 1])) 
								isPalindrome = false;
				}
				cout << s << " -- is ";
				if (isMirror && isPalindrome)
						cout << ans[3];
				else if (isMirror && !isPalindrome)
						cout << ans[2];
				else if (!isMirror && isPalindrome)
						cout << ans[1];
				else
						cout << ans[0];
				cout << endl;
		}
}



				  
