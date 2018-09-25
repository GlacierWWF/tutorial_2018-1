// week_1 task_programming_exercise

#include<iostream>
#include<string>
#include<set>
using namespace std;

char findMirror(char);
bool isMirroredLetter(char);
bool isMirroredPalindrome(string);
bool isMirroredString(string);
bool isRegularPalindrome(string);

int main()
{
    string s;
    while(cin>>s)
    {   
        if(isMirroredPalindrome(s))
        {
            cout << s << " -- is a mirrored palindrome." << endl;

        }
        else if(isMirroredString(s))
        {
            cout << s << " -- is a mirrored string." << endl;
        }
        else if(isRegularPalindrome(s))
        {
            cout << s << " -- is a regular palindrome." << endl;
        }
        else
        {
            cout << s << " -- is not a palindrome." << endl;
        }
        
    }
}


bool isMirroredLetter(char c)
{
    set<char> cSet={'A','H','I','M','O','T','U','V','W','X','Y','1','8'};

    auto search= cSet.find(c);
    {
        if(search!=cSet.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

char findMirror(char c)
{
    string character = "AEHIJLMOSTUVWXYZ12358";
    string chReserve = "A3HILJMO2TUVWXY51SEZ8";
    auto search = character.find(c);
    if(search<=character.size())
    {
        return chReserve[search];
    }
    else
    {
        return '#';
    }
}

bool isMirroredPalindrome(string s)
{
    bool flag=true;
    for(int i=0;i<=s.size()/2;i++)
    {
        if(!(isMirroredLetter(s[i])&&s[i]==s[s.size()-i-1]))
        {
            flag=false;
            break;
        }
    }
    return flag;

}

bool isMirroredString(string s)
{
    bool flag = true;
    for (int i = 0; i <= s.size() / 2;i++)
    {
        if(s[i]!=findMirror(s[s.size()-i-1]))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool isRegularPalindrome(string s)
{
    bool flag = true;
    for (int i = 0; i < s.size() / 2;i++)
    {
        if(s[i]!=s[s.size()-i-1])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

