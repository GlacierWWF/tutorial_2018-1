#include <iostream>
#include <string.h>
using namespace std;
#define N 1000

bool isregular(char a[N])
{
    int len=strlen(a);
    for(int i=0;i<(len/2);i++)
        {if(a[i]!=a[len-1-i]) return false;}
    return true;
}

char mirror(char a)
{
    switch(a)
    {
    case 'A':
        return 'A';
    case 'E':
        return '3';
    case 'H':
        return 'H';
    case 'I':
        return 'I';
    case 'J':
        return 'L';
    case 'L':
        return 'J';
    case 'M':
        return 'M';
    case 'O':
        return 'O';
     case 'S':
        return '2';
    case 'T':
        return 'T';
    case 'U':
        return 'U';
    case 'V':
        return 'V';
    case 'W':
        return 'W';
    case 'X':
        return 'X';
    case 'Y':
        return 'Y';
    case 'Z':
        return '5';
    case '1':
        return '1';
    case '2':
        return 'S';
    case '3':
        return 'E';
    case '5':
        return 'Z';
    case '8':
        return '8';

    }

}

bool ismirror(char a[N])
{
    int len=strlen(a);
    for(int i=0;i<=(len/2);i++)
        {
            if(a[i]!=mirror(a[len-1-i]) )return false;}
    return true;
}


int main()
{
   char a[N];

   cin>>a;
   if(isregular(a)&&!ismirror(a)) cout<<a<<"-- is a regular palindrome."<<endl;
  if(!isregular(a)&&!ismirror(a))cout<<a<<"-- is not a palindrome."<<endl;
   if(!isregular(a)&&ismirror(a))cout<<a<<"-- is a mirrored string."<<endl;
   if(isregular(a)&&ismirror(a)) cout<<a<<"-- is a mirrored palindrome."<<endl;
    return 0;
}

