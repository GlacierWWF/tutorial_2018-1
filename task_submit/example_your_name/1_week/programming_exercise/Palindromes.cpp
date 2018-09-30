#include <iostream>
#include <string>
using namespace std;
int main()
{
	string test;
	int len=0,tru_p=0,tru_m=0;
	int i=0,j=0;
	cin>>test;
	len = test.size();
	
	/*test if the string is a palindrome*/
	for( i=0; i<len/2 ; i++)
	{
		if(test[i]!=test[len-1-i])
		break;
	}
	if(len%2 == 0 && i == len/2 && test[i] == test[i-1] )
		tru_p = 1;
	else if(len%2 == 1 && i == len/2 && test[i-1] == test[i+1] )
		tru_p = 1;
	else;
	
	/*test if the string is a mirror*/
	for( i=0; i<len/2 ; i++)
	{
		if(test[i]=='B' || test[i]=='C' || test[i]=='D' || test[i]=='F' || test[i]=='G' || test[i]=='K' || test[i]=='N' || test[i]=='P' || test[i]=='Q' || test[i]=='R' || test[i]=='4' || test[i]=='6' || test[i]=='7' || test[i]=='9') 
		break;
		else if(test[i] == 'A' && test[len-1-i] != 'A') break;
		else if(test[i] == 'E' && test[len-1-i] != '3') break;
		else if(test[i] == 'H' && test[len-1-i] != 'H') break;
		else if(test[i] == 'I' && test[len-1-i] != 'I') break;
		else if(test[i] == 'J' && test[len-1-i] != 'L') break;
		else if(test[i] == 'L' && test[len-1-i] != 'J') break;
		else if(test[i] == 'M' && test[len-1-i] != 'M') break;
		else if(test[i] == 'O' && test[len-1-i] != 'O') break;
		else if(test[i] == 'S' && test[len-1-i] != '2') break;
		else if(test[i] == 'T' && test[len-1-i] != 'T') break;
		else if(test[i] == 'U' && test[len-1-i] != 'U') break;
		else if(test[i] == 'V' && test[len-1-i] != 'V') break;
		else if(test[i] == 'W' && test[len-1-i] != 'W') break;
		else if(test[i] == 'X' && test[len-1-i] != 'X') break;
		else if(test[i] == 'Y' && test[len-1-i] != 'Y') break;
		else if(test[i] == 'Z' && test[len-1-i] != '5') break;
		else if(test[i] == '1' && test[len-1-i] != '1') break;
		else if(test[i] == '2' && test[len-1-i] != 'S') break;
		else if(test[i] == '3' && test[len-1-i] != 'E') break;
		else if(test[i] == '5' && test[len-1-i] != 'Z') break;
		else if(test[i] == '8' && test[len-1-i] != '8') break;
		else;
	}
	if(len%2 == 0 && i == len/2)
		tru_m = 1;
	else if(len%2 == 1 && i == len/2 && (test[i] == 'A'||test[i] == 'H'||test[i] == 'I'||test[i] == 'O'||test[i] == 'M'||test[i] == 'T'||test[i] == 'U'||test[i] == 'V'||test[i] == 'W'||test[i] == 'X'||test[i] == 'Y'||test[i] == '1'||test[i] == '8') )
		tru_m = 1;
	else;
	
	//output
	cout<<test<<" -- ";
	if(tru_p == 0 && tru_m == 0) cout<<"is not a palindrome."<<endl;
	if(tru_p == 1 && tru_m == 0) cout<<"is a regular palindrome."<<endl;
	if(tru_p == 0 && tru_m == 1) cout<<"is a mirrored string."<<endl;
	if(tru_p == 1 && tru_m == 1) cout<<"is a mirrored palindrome."<<endl;
	
	
	return 0;
}
