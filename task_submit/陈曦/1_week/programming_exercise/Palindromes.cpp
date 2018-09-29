#include<iostream>
#include<cstring>
#include<map>
#include<cstdio>

using namespace std;

int is_palindrome();
int is_mirror();
char a[50];
map<char,char> mirror_map;

int main()
{
	while(scanf("%s",a)!=EOF)
	{

        if(is_palindrome())
        {
            if(is_mirror())
                cout << a << " -- is a mirrored palindrome." << endl;
            else
                cout << a << " -- is a regular palindrome." << endl;
        }
        else
        {
            if(is_mirror())
                cout << a << " -- is a mirrored string." << endl;
            else
                cout << a << " -- is not a palindrome." << endl;
        }
        cout<<endl;
        memset(a,0,sizeof(a));
	}
	return 0;
}

int is_palindrome()
{
	int len = strlen(a);
	int reverse = len - 1;
	int count = 0;
	for (int i = 0; i < len /2; ++i)
	{
		if (a[i] == a[reverse])
		{
			count ++;
			reverse --;
		}
	}
	if(count == len /2)
		return 1;
    return 0;
}

int is_mirror()
{
	mirror_map['A']='A';
    mirror_map['B']='*';
    mirror_map['C']='*';
    mirror_map['D']='*';
    mirror_map['E']='3';
    mirror_map['F']='*';
    mirror_map['G']='*';
    mirror_map['H']='H';
    mirror_map['I']='I';
    mirror_map['J']='L';
    mirror_map['K']='*';
    mirror_map['L']='J';
    mirror_map['M']='M';
    mirror_map['N']='*';
    mirror_map['O']='O';
    mirror_map['P']='*';
    mirror_map['Q']='*';
    mirror_map['R']='*';
    mirror_map['S']='2';
    mirror_map['T']='T';
    mirror_map['U']='U';
    mirror_map['V']='V';
    mirror_map['W']='W';
    mirror_map['X']='X';
    mirror_map['Y']='Y';
    mirror_map['Z']='5';
    mirror_map['1']='1';
    mirror_map['2']='S';
    mirror_map['3']='E';
    mirror_map['4']='*';
    mirror_map['5']='Z';
    mirror_map['6']='*';
    mirror_map['7']='*';
    mirror_map['8']='8';
    mirror_map['9']='*';
    int len = strlen(a);
	int reverse = len - 1;
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (a[i] == mirror_map[a[reverse]])
		{
			count ++;
			reverse --;
		}
	}
	if(count == len)
		return 1;
	return 0;

}