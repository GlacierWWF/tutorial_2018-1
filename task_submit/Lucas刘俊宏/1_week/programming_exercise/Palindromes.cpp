#include <iostream>
#include <cstring>
using namespace std;
const char rev[100]={'A','3','H','I','L','J','M','O','2','T','U','V','W','X','Y', '5','1','S','E','Z','8'};
int main(int argc, const char * argv[])
{
    char str[100];
    while(cin >> str)
    {
        int i = 0;
        int p = 1,q = 1;
        int len = (int)strlen(str);
        int count = 0;
        for(int j = 0;j < len;j++)
        {
            if(str[j] != str[len - j - 1])  //判断是否为回文，若不是,p=0
            {
                p = 0;
            }
        }
        for(int j = 0;j < 21;j++)
        {
            for(i = 0;i < len;i++)  //判断是否为镜像，若不是,q=0
            {
                if(str[i] == rev[j])
                {
                    count++;
                }
            }
        }
        if(count != len)
        {
            q = 0;
        }
        if(p == 0 && q == 1)    //if the string is not a palindrome and is a mirrored string
        {
            cout << str << " -- is a mirrored string." << endl;
        }
        if(q == 0 && p == 0)    //if the string is not a palindrome and is not a mirrored string
        {
            cout << str << " -- is not a palindrome." << endl;
        }
        if(p == 1 && q == 0)    //if the string is a palindrome and is not a mirrored string
        {
            cout << str << " -- is a regular palindrome." << endl;
        }
        if(p == 1 && q == 1)    //if the string is a palindrome and is a mirrored string
        {
            cout << str << " -- is a mirrored palindrome." << endl;
        }
    }
    return 0;
}
