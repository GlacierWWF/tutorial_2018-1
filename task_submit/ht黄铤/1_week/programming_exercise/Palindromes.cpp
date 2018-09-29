#include<iostream>
#include<string.h>
using namespace std;

int flagp=1,flagm;

void pal(char ch[])
{
	int l=strlen(ch);
	for(int i=0;i<l;i++)
	{
		if(ch[i]!=ch[l-i-1])
			flagp=0;
	}
}

void mir(char ch[])
{
	int l=strlen(ch);
	for(int i=0;i<l;i++)
	{
		if((ch[i]=='A')||(ch[i]=='H')||(ch[i]=='I'||(ch[i]=='M')||(ch[i]=='O')||(ch[i]=='T')||(ch[i]=='U')||(ch[i]=='V')||(ch[i]=='W')||(ch[i]=='X')||(ch[i]=='Y')||(ch[i]=='1')||(ch[i]=='8')))
		{
			if(ch[i]==ch[l-i-1]) {flagm=1;continue;}
			else {flagm=0;break;}
		}
		if((ch[i]=='E'&&ch[l-i-1]=='3')||(ch[i]=='3'&&ch[l-i-1]=='E')||
		 (ch[i]=='J'&&ch[l-i-1]=='L')||(ch[i]=='L'&&ch[l-i-1]=='J')||
		 (ch[i]=='S'&&ch[l-i-1]=='2')||(ch[i]=='2'&&ch[l-i-1]=='S')||
		 (ch[i]=='Z'&&ch[l-i-1]=='5')||(ch[i]=='5'&&ch[l-i-1]=='Z'))
		{
			flagm=1;continue;
		}
		else {flagm=0;break;}
	}
}
int main()
{
	char cha[21];
	cin>>cha;
	int l=strlen(cha);
	cout<<cha<<' ';
	pal(cha);
	mir(cha);
	if(flagm==0&&flagp == 0)
	{cout<<"is not a palindrome.\n"<<endl;}		
	else if(flagm==1&&flagp==1)
	{cout<<"is a mirrored palindrome.\n"<<endl;}		
	else if(flagp==1&&flagm==0)
	{cout<<"is a regular palindrome.\n"<<endl;}		
	else if(flagp==0&&flagm==1)
	{cout<<"is a mirrored string.\n"<<endl;}
			
}
