#include<iostream>
#include<string>
#include<map>
using namespace std;
bool isMirrored(string s)
{
	//Every valid character is mapped to its mirrored character
	//The space ' ' is mapped if the character has no mirrored character
	map<char,char> m={	{'A','A'},{'B',' '},{'C',' '},{'D',' '},{'E','3'},
						{'F',' '},{'G',' '},{'H','H'},{'I','I'},{'J','L'},
						{'K',' '},{'L','J'},{'M','M'},{'N',' '},{'O','O'},
						{'P',' '},{'Q',' '},{'R',' '},{'S','2'},{'T','T'},
						{'U','U'},{'V','V'},{'W','W'},{'X','X'},{'Y','Y'},
						{'Z','5'},{'1','1'},{'2','S'},{'3','E'},{'4',' '},
						{'5','Z'},{'6',' '},{'7',' '},{'8','8'},{'9',' '}};
		if(s.empty())
		return true;
	for(int i=0;i<=s.size()/2;++i)
		if(m[s[i]]!=s[s.size()-1-i])
			return false;
	return true;
}
bool isPalindrome(string s)
{
		for(int i=0;i<s.size()/2;++i)
		if(s[i]!=s[s.size()-1-i])
			return false;
	return true;
}
int main()
{
	string s;
	while(cin>>s)
	{
		if(isPalindrome(s))
			if(isMirrored(s))
				cout<<s<<" -- is a mirrored palindrome."<<endl<<endl;
			else
				cout<<s<<" -- is a regular palindrome."<<endl<<endl;
		else
			if(isMirrored(s))
				cout<<s<<" -- is a mirrored string."<<endl<<endl;
			else
				cout<<s<<" -- is not a palindrome."<<endl<<endl;
	}
	return 0;
}
