#include <stdio.h>
#include<string.h>
#include<ctype.h>
const char * cov="A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char * coc[] = {"not a palindrome","a regular palindrome","a mirrored string","a mirrored palindrome"};


int main()
{
    char g(char r);
    char s[35];
    scanf("%s",s);
    int len=strlen(s);
    int p=1;
    int j=1;
    int k=(len + 1) / 2;
    for (int i=0;i<k;i++)
    {
        if (s[i]!=s[len-1-i])
        {
            p=0;
        }
        if (g(s[i])!=s[len-1-i])
        {
            j=0;
        }
    }
    printf("%s -- is %s.\n",s,coc[j*2+p]);
    return 0;
}

char g (char r)
    {
        if(isdigit(r))
        {
            return cov[r-'0'+25];
        }
        return cov[r-'A'];
    }

