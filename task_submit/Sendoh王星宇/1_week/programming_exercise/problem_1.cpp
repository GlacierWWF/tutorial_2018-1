#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

//×Ö·ûÊı×é´æ·Å×Ö·û¾µÏñ
const char reverse[50]="A   3  HIL JM O   2TUVWXY51SE Z  8 ";

//·µ»Ø¾µÏñ×Ö·û 
char func(char ch)
{
	if(isalpha(ch))
	{
		return reverse[ch-'A'];
	}
	return reverse[ch-'0'+25];
}

int main()
{
	//Êı×éÖ¸Õë´æ·ÅÊä³ö 
	const char* output[] = {"not a palindrome","a regular palindrome","a mirrored string","a mirrored palindrome"}; 
	
	char str[25];
    
    while(scanf("%s",str)==1)
	{
		int len=strlen(str);
		int judge1=1,judge2=1;//ÅĞ¶Ï 
		for(int i=0;i<len/2;i++)
		{
			if(str[i]!=str[len-i-1])
	        judge1=0;
	        if(func(str[i])!=str[len-1-i])
	        judge2=0;
	    } 
	    cout<<str<<" -- is "<<output[judge1+2*judge2]<<endl<<endl; 
    } 
	return 0;
}
