/******************************************************
* Palindromes
*
* Determine if a string is a regular palindrome or not
* or a mirrored string or a mirrored palindrome
*
* @author   JackkiiChen
* @email    chenjq66@mail2.sysu.edu.cn
* @version  1.0.0.0
* @date     2018/09/19
*
*******************************************************/

//System Headers
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
* @brief reverse mirror char array
*/
const char mirr[]=
{   //A-Z
    'A',' ',' ',' ','3',' ',' ','H','I','L',' ','J','M',
    ' ','O',' ',' ',' ','2','T','U','V','W','X','Y','5',
    //1-9
    '1','S','E',' ','Z',' ',' ','8',' '
};

/**
* @brief reverse mirror character return function
*
* @param c   the character prepare to be reversed(mirror)
*
* @return char  the reverse mirror character
*/
char m(char c)
{
    if('A'<=c&&c<='Z')return mirr[c-'A'];
        return mirr[c-'0'+25];
}

/**
* @brief Palindrome Main Function
*
* @return integer
*/
int main()
{
    string str,str0;//str:the input string
                    //str0:the copy of str
    while(cin>>str)
    {
        bool isrp=true,ismp=true;//isrp: if the regular palindrome
                                //ismp:if the mirror palindrome
        str0=str;

        //judge if regular palindrome
        reverse(str.begin(),str.end());
        if(str0!=str)
            isrp=false;

        //judge if mirror palindrome
        int len=str0.length();
        for(int i=0;i<(len+1)/2;i++)
            if(m(str0[i])!=str0[len-1-i])
            {
                ismp=false;
                break;
            }
        //print out the result
        if(ismp==false&&isrp==false)cout<<str0<<" -- is not a palindrome."<<endl;
        if(ismp==false&&isrp==true)cout<<str0<<" -- is a regular palindrome."<<endl;
        if(ismp==true&&isrp==false)cout<<str0<<" -- is a mirrored string."<<endl;
        if(ismp==true&&isrp==true)cout<<str0<<" -- is a mirrored palindrome."<<endl;
    }
    return 0;
}


