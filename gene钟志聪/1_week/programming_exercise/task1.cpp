#include<iostream>
#include<string>
using namespace std;

bool judgePlaindrome(const string s);
bool judgeMirror(string s);

int main()
{
	string s;
	
	while( cin >> s )
	{
		if( judgePlaindrome(s) )
		{
			if( judgeMirror(s) )
			{
				cout << s << " -- is a mirrored palindrome." << endl;
			}else{
				cout << s << " -- is a regular palindrome." << endl;
			}
		}else{
			if( judgeMirror(s) )
			{
				cout << s << " -- is a mirrored string." << endl;
			}else{
				cout << s << " -- is not a palindrome." << endl;
			}
		}
	}
	return 0;	
} 

bool judgePlaindrome(const string s)
{
	for( int i = 0; i < s.length(); i++ )
	{
		if( s[i] != s[s.length()-i-1])
			return false;
	}
	
	return true;
}
bool judgeMirror(string s)
{
	for( int i = 0; i < s.length(); i++ )
	{
		switch(s[i]){
			case 'B':
			case 'C':
			case 'D':
			case 'F':
			case 'G':
			case 'K':
			case 'N':
			case 'P':
			case 'Q':
			case 'R':
			case '4':
			case '6':
			case '7':
			case '9':
				return false;
		}
		
		if( s[i] == 'A' && s[s.length() - i - 1] != 'A' )
			return false;
		if( s[i] == 'E' && s[s.length() - i - 1] != '3' )
			return false;
		if( s[i] == 'H' && s[s.length() - i - 1] != 'H' )
			return false;
		if( s[i] == 'J' && s[s.length() - i - 1] != 'L' )
			return false;
		if( s[i] == 'L' && s[s.length() - i - 1] != 'J' )
			return false;
		if( s[i] == 'M' && s[s.length() - i - 1] != 'M' )
			return false;
		if( s[i] == 'O' && s[s.length() - i - 1] != 'O' )
			return false;
		if( s[i] == 'S' && s[s.length() - i - 1] != '2' )
			return false;
		if( s[i] == 'T' && s[s.length() - i - 1] != 'T' )
			return false;
		if( s[i] == 'U' && s[s.length() - i - 1] != 'U' )
			return false;
		if( s[i] == 'V' && s[s.length() - i - 1] != 'V' )
			return false;
		if( s[i] == 'W' && s[s.length() - i - 1] != 'W' )
			return false;
		if( s[i] == 'X' && s[s.length() - i - 1] != 'X' )
			return false;
		if( s[i] == 'Y' && s[s.length() - i - 1] != 'Y' )
			return false;
		if( s[i] == 'Z' && s[s.length() - i - 1] != '5' )
			return false;
		if( s[i] == 'Q' && s[s.length() - i - 1] != 'Q' )
			return false;
		if( s[i] == '2' && s[s.length() - i - 1] != 'S' )
			return false;
		if( s[i] == '3' && s[s.length() - i - 1] != 'E' )
			return false;
		if( s[i] == '5' && s[s.length() - i - 1] != 'Z' )
			return false;
		if( s[i] == '8' && s[s.length() - i - 1] != '8' )
			return false;
	}
	return true;
}

