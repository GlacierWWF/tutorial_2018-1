/* Title: palindromes.cpp
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-09-22
 * Version: 1.0.0
 * Abstract: A program to determine if the input string is mirrored or a palindrome.
 */

#include<iostream>
#include<cctype>
#include<cstring>
using namespace std;

char mirrored_char[30] = "A***3**HIL*JM*O***2TUVWXY5";
char mirrored_num[10] = "1SE*Z**8*";
char temp[100];

char mirror(char c){
	if (c >= 'A' && c <= 'Z') return mirrored_char[c - 'A'];
	if (c >= '1' && c <= '9') return mirrored_num[c - '1'];
}

int main()
{
	cout << "Please enter strings, at the end of each string, press ENTER to process." << endl;
	while (cin >> temp)
	{
		int length = strlen(temp);
		int ispalin = 1;
		int ismirr  = 1;
		for (int i = 1; i <= (0.5*length); i++){
			if (temp[i] != temp[length-i-1])           ispalin = 0;
			if (temp[i] != mirror(temp[length-i-1]))   ismirr  = 0;
		}

		if (ispalin == 0 && ismirr == 0) cout << temp << " --is not a palindrome." << endl;
		else if (ispalin == 1 && ismirr == 0) cout << temp << " --is a regular palindrome." << endl;
		else if (ispalin == 0 && ismirr == 1) cout << temp << " --is a mirrored string." << endl;
		else if (ispalin == 1 && ismirr == 1) cout << temp << " --is a mirrored palindorme." << endl;
		else cout << "An error occured. " << endl;
	}
}
