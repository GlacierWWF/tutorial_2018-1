#include<bitset>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
void solve(int m,string *k)
{
	string binary[m];
	for(int i=0;i<m;i++)
	{
		int pos = 0;
		int dot_num = 1;
		int size;
		string temp =k[m];
		string sub1,sub2,sub3,sub4;
		int num1,num2,num3,num4;
		int p[5];//p[1],p[2],p[3]
		for(int i= 0;i<temp.size();i++)
		{
			if(temp[i]=='.')
			{
				p[dot_num] = i;
				dot_num++;
			}
			if(dot_num==4)
			break;
		}
		sub1 = temp.substr(0,p[1]);
		sub2 = temp.substr(p[1]+1,p[2]-p[1]);
		sub3 = temp.substr(p[2]+1,p[3]-p[2]);
		sub4 = temp.substr(p[3]+1,temp.size()-1-p[3]);
		char b1[4],b2[4],b3[4],b4[4];
		strcpy(b1,sub1.c_str());
		strcpy(b2,sub2.c_str());
		strcpy(b3,sub3.c_str());
		strcpy(b4,sub4.c_str());
		num1 = atoi(b1);
		num2 = atoi(b2);
		num3 = atoi(b3);
		num4 = atoi(b4);
		string change1,change2,change3,change4;
		bitset<8> set1,set2,set3,set4;
		set1 = num1;
		set2 = num2;
		set3 = num3;
		set4 = num4;
		change1 =set1.to_string();
		change2 =set2.to_string();
		change3 =set3.to_string();
		change4 =set4.to_string();
		binary[m] = change1+change2+change3+change4;
			
	}
	string standard = binary[0];
	int wangluo_bit;
	for(int i=0;i<32;i++)
	{
		int j;
		for(j=0;j<m;j++)
		{
			string temp = binary[j];
			if(temp[i]!=standard[i])
			{
				break;
			}
		}
		if(j!=m)
		{
			wangluo_bit = j+1;//网络号位数
			break;
		}
	}
	int ziwang_mask[32];
	int wangluo_addr[32];
	for(int i=0;i<wangluo_bit;i++)
	{
		ziwang_mask[i]=1;
		wangluo_addr[i]=standard[i] - 48;
	}
	for(int j=wangluo_bit;j<32;j++)
	{
		ziwang_mask[j]=0;
		wangluo_addr[j]=0;
	}
	int wl[4];
	int mask[4];
	for(int i=0;i<4;i++)
	{
		
		wl[i] = wangluo_addr[i*8]+wangluo_addr[i*8+1]*2+wangluo_addr[i*8+2]*4+wangluo_addr[i*8+3]*8+wangluo_addr[i*8+4]*16+wangluo_addr[i*8+5]*32+wangluo_addr[i*8+6]*64+wangluo_addr[i*8+7]*128;
	}
	for(int i=0;i<4;i++)
	{
		
		mask[i] = ziwang_mask[i*8]+ziwang_mask[i*8+1]*2+ziwang_mask[i*8+2]*4+ziwang_mask[i*8+3]*8+ziwang_mask[i*8+4]*16+ziwang_mask[i*8+5]*32+ziwang_mask[i*8+6]*64+ziwang_mask[i*8+7]*128;
	}
	cout<<wl[0]<<"."<<wl[1]<<"."<<wl[2]<<"."<<wl[3]<<endl;
	cout<<mask[0]<<"."<<mask[1]<<"."<<mask[2]<<"."<<mask[3]<<endl;
	
}

int main()
{
	int m;
	string k[1000];
	cin>>m;
	int po =0;
	while(po<=m)
	{
		cin>>k[po];
		po++;
	}
	solve(m,k);
	
	
	
}
