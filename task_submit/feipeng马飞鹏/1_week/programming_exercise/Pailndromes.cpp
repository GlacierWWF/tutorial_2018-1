#include<iostream>
#include<string> 
using namespace std;
const char change_before[]={'3','L','2','5'};
const char change_after[]= {'E','J','S','Z'};
const char cannotbe[] = {'B','C','D','F','G','K','N','P','Q','R','4','6','7','9'};
void solve(string &k)
{
	string input = k;
	int len = input.size();			
	int times = len/2;	
	bool regular,mirror;			
	int i,j;
	for(i = 0;i<times;i++)
	{
		if(input[i]!=input[len-1-i])
		break;
	}
	if(i==times) regular = true;
	else regular = false;
		
	
		for(i=0;i<len;i++)
		{
			for(j=0;j<4;j++)
			{
				if(input[i] == change_before[j])
					input[i] = change_after[j];	 
			} 
		}
		for(i = 0;i<times;i++)
	{
		if(input[i]!=input[len-1-i])
		break;
	}
	if(i==times) mirror = true;
	else mirror = false;
	for(i=0;i<14;i++)
	{
		if(input[times+1] == cannotbe[i])
		break;
	}
	if(i!=14)	
	mirror = false;		
	cout<<k;
	if(regular==false&&mirror==false) cout<<"-- is not a palindrome."<<endl;
	if(regular==true&&mirror==false)  cout<<"-- is a regular palindrome."<<endl;
	if(regular==false&&mirror==true)  cout<<"-- is a mirrored string."<<endl;
	if(regular==true&&mirror==true)  cout<<"-- is a mirrored palindrome."<<endl;
}
int main()
{
	string k;
	while(cin>>k)
	{
	solve(k);
	cout<<endl;
	}
	return 1;
}
