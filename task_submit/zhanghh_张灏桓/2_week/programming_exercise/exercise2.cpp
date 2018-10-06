//Author:zhanghaohuan
//Revised:zhanghaohuan
//Date:2018_10_6
//Version:v1.0.0
//Abstract:Programing exercise week2 - IP Networks


#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

int m;
ll flag[33];
 
void initial()
{
  for(int i = 0; i <= 32; i++) 
  {
    flag[i] = -1;
  }
}
 
void solve()
{
  while(m--)
  {
		ll a, b, c, d;
		scanf("%lld.%lld.%lld.%lld", &a, &b, &c, &d);	
		ll x = a * (1<<24) + b * (1<<16) + c * (1<<8) + d;
		
		for(int i = 0; i < 32; ++i)
    {
			int temp = ((x>>i) & 1);
			if(flag[i] != -1 && flag[i] != temp)
				flag[i] = 2;
			else
			  flag[i] = temp;
		}		
	}
	
	int end;
	for(int i = 31; i >= 0; i--)
	{
		if(flag[i] == 2)
		{
		  end = i;
		  break;
		}
	}

	ll ip = 0, mask = 0, add = 1;
	for(int i = 0; i < 32; i++, add <<= 1){
		if(i > end){
			ip += flag[i] * add;
			mask += add;
		}
	}
	printf("%lld.%lld.%lld.%lld\n", ip>>24, (ip>>16) % (1<<8), (ip>>8) % (1<<8), ip % (1<<8));
	printf("%lld.%lld.%lld.%lld\n", mask>>24, (mask>>16) % (1<<8), (mask>>8) % (1<<8), mask % (1<<8));
}

int main()
{
	while(scanf("%d",&m) != EOF)
	{ 
	  initial();
	  solve();
  }
	return 0;	
} 

