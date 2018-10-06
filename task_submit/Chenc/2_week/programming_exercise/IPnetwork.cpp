/*Title:IPnetwork.cpp
  *Author:Chen Ruijia
  *Revised:Chen Ruijia
  *Date:2018-10-04
  *Version:1.0.0
  *Abstract: A program to caculate network mask and network adress depending on input IP addresses
  */
#include<iostream> 
#include<cstring>
#include<cstdio>
#include"IP.hpp"
using namespace std;
IP::IP()
{	
	memset(this->Bin, 0, sizeof(this->Bin));
	memset(this->Dec, 0, sizeof(this->Dec));
}
bool morethan(IP a, IP b)
{
	for (int i = 0; i < 4; i++)
	{
		if (a.Dec[i] > b.Dec[i])
			return true;
		else if (a.Dec[i] < b.Dec[i])
			return false;
	}
	return false;
}
bool lessthan(IP a, IP b)
{
	for (int i = 0; i < 4; i++)
	{
		if (a.Dec[i] < b.Dec[i])
			return true;
		else if (a.Dec[i] > b.Dec[i])
			return false;
	}
	return false;
}

void dec2bin(IP &a)
{
	int temp;
	memset(a.Bin, 0, sizeof(a.Bin));
	for (int p = 0; p < 4; p++)
	{
		temp = a.Dec[p];
		for (int q = 7; q >= 0; q--)
		{
			if (temp == 0)
				break;
			a.Bin[p][q] = temp % 2;
			temp = temp / 2;
		}
	}
}
void bin2dec(IP &b)
{
	memset(b.Dec, 0, sizeof(b.Dec));
	for (int p = 0; p < 4; p++)
	{
		for (int q = 0; q < 8; q++)
		{
			b.Dec[p] = b.Dec[p] * 2;
			b.Dec[p] += b.Bin[p][q];
		}
	}
}
void check(IP &MIN1, IP &MAX1)//return internet mask
{
	bool a=false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (a)
			{
				MIN1.Bin[i][j] = 0;
				MAX1.Bin[i][j] = 0;
			}
			else
			{
				if (MIN1.Bin[i][j] != MAX1.Bin[i][j])
				{
					a = 1;
					MIN1.Bin[i][j] = 0;
					MAX1.Bin[i][j] = 0;
				}
				else
					MAX1.Bin[i][j] = 1;
			 }
		}
	}
}
int main()
{
	IP  temp, MAX, MIN;
	int m;
	cout << "Please enter the number of IPnetwork : ";
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 4; j++)
			scanf("%d%*c", &temp.Dec[j]);
		if (i == 0)
		{
			MAX = temp;
			MIN = temp;
		}
		else
		{
			if (morethan(temp, MAX))
				MAX = temp;
			else if (lessthan(temp, MIN))
				MIN = temp;
		}
		
		
	}
	dec2bin(MIN);
	dec2bin(MAX);
	check(MIN, MAX);
	bin2dec(MIN);
	bin2dec(MAX);
	cout << MIN.Dec[0] << "." << MIN.Dec[1] << "." << MIN.Dec[2] << "." << MIN.Dec[3] << endl;
	cout << MAX.Dec[0] << "." << MAX.Dec[1] << "." << MAX.Dec[2] << "." << MAX.Dec[3] << endl;
	return 0;
}
