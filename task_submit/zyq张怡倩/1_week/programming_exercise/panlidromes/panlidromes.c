#include <iostream>
#include <string>
using namespace std;
int main()
{
 int t=0,p=0;
 string s;
 cin>>s;
 int rev[100]={0};
 rev['A']='A';rev['E']='3';rev['H']='H';rev['I']='I';rev['J']='L';
 rev['L']='J';rev['M']='M';rev['O']='O';rev['S']='2';rev['T']='T';
 rev['U']='U';rev['V']='V';rev['W']='W';rev['X']='X';rev['Y']='Y';
 rev['Z']='5';rev['1']='1';rev['2']='S';rev['3']='E';rev['5']='S';
 rev['8']='8';
 for(int i=0;i<s.length()/2;i++)            //判断是否镜像
 {
  if(s[i]!=rev[s[s.length()-i-1]])
  {
   p=1;
   break;
  }
 }
 for(int i=0;i<s.length()/2;i++)           //判断是否回文
 {
  if(s[s.length()-i-1]!=s[i])
  {
   t=1;
   break;
  }
 }
 if(t==1&&p==1)                                //输出
 cout<<s<<" -- is not a palindrome."<<endl;
 else if(t!=1&&p==1)
 cout<<s<<" -- is a regular palindrome."<<endl;
 else if(t==1&&p!=1)
 cout<<s<<" -- is a mirrored string."<<endl;
 else if(t!=1&&p!=1)
 cout<<s<<" -- is a mirrored palindrome."<<endl;
}

