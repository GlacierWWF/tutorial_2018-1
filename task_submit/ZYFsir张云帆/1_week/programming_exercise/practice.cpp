#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


string replace(string str,string rep_1,string rep_2);

int main()
{
	string rep_1="EJLSZ2350";
	string rep_2="3LJ25SEZO";
	while(1)
	{
		string str;
		int flag=0;
		cin>>str;
		string str_reverse=str;
		reverse(str_reverse.begin(),str_reverse.end());
		//cout<<str_reverse<<endl;
		if(str==str_reverse)
			{flag+=1;}
		//cout<<"Ready to replace"<<endl;
		str_reverse=replace(str_reverse,rep_1,rep_2);
		if(str==str_reverse)
			{flag+=10;}
		//cout<<str_reverse<<endl;
		//cout<<"flag: "<<flag<<endl;
		switch(flag)
		{
			case 0:
				cout<<"--is not a palindrome."<<endl;
				break;
			case 1:
				cout<<"--is a regular palindrome."<<endl;
				break;
			case 10:
				cout<<"--is a mirrored string."<<endl;
				break;
			case 11:
				cout<<"--is a mirrored palindrome."<<endl;
				break;
			default:
				break;


		}
	}
	return 0;
}

string replace(string str,string rep_1,string rep_2)
{
	int pos=0;int i=0;
	cout<<"size: "<<rep_1.size()<<endl;
	while(pos<str.size())
	{
		i=0;
		while(i<rep_1.size())
		{
			if(str[pos]==rep_1[i])
			{	
				//cout<<"recognize: "<<str[pos]<<" on "<<pos<<endl;
				//cout<<"i: "<<i<<endl;
				str[pos]=rep_2[i];
				break;	
			}
			i++;
		}
		++pos;
		//cout<<"pos: "<<pos<<endl;
	}
	//cout<<"replace done"<<endl;
	return str;
	
}
