#include<iostream>
#include<string> 
using namespace std;
const char change_before[]={'3','L','2','5'};	//将对称的词改成同一个
const char change_after[]= {'E','J','S','Z'};
const char every_cannotbe[] = {'B','C','D','F','G','K','N','P','Q','R','4','6','7','9'};
const char mid_cannotbe[]={'E','3','J','L','S','2','Z','5','1'};
/*
 *思路：先判断是否为普通的对称字符串，再将原字符串中的对称的字母成同一个,再判断是否为对称字符串，
 *注意此时还不能判断是否为镜像字符串，还要注意每一个字符都不能为非对称字符，然后如果字符串长度
 *为奇数，则中间的字符必须自身对称。
 * */
void solve(string &k)
{
	string input = k;//input为被处理的字符串
	int len = input.size();//len为字符串长度			
	int times = len/2;	//tiems为字符串半长
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
 	for(i=0;i<len;i++)
	{
		for(j=0;j<14;j++)
		{
			if(input[i] == every_cannotbe[j])
				break;
		}
		if(j!=14) mirror = false;
	}
	if(len%2!=0)
	{
	for(i=0;i<9;i++)
	{
		if(input[times] ==mid_cannotbe[i])
		break;
	}
	if(i!=9)	
	mirror = false;		
	}
	cout<<k;
	if(regular==false&&mirror==false) cout<<" -- is not a palindrome."<<endl;
	if(regular==true&&mirror==false)  cout<<" -- is a regular palindrome."<<endl;
	if(regular==false&&mirror==true)  cout<<" -- is a mirrored string."<<endl;
	if(regular==true&&mirror==true)  cout<<" -- is a mirrored palindrome."<<endl;
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
