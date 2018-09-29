#include <iostream>
#include <string>
using namespace std;

char reserve(char input)//The fuction returns the mirrored character of the input character
{
	string str = "A~~~3~~HIL~JM~O~~~2TUVWXY51SE~Z~~8~";
	//establish a string array whitch contain the mirrored character of alphas A~Z and numbers 1~9
	if (isalpha(input))//distinguish alphas and numbers
		return str[input - 65];
	else
		return str[input - 23];
}
int main()
{
	int N;
	cout << "Please enter the number of strings needed to check(1<N<20) : ";
	cin >> N;
	if (N< 1 || N>20)
		cout << "Not valid" << endl;
	cin.ignore();//using cin.ignore() to sovle the confict of "cin<<" and "cin.getline()"
	for (int j = 0; j < N; j++)
	{
		string str = "A~~~3~~HIL~JM~O~~~2TUVWXY51SE~Z~~8~";
		int a = str.length();
		string inputstr;
		getline(cin, inputstr);
		//inputstr = cin.getline(); 
		//seems that the cin.getline() function works not very well
		string inputstr2 = inputstr;
		int m = inputstr.length();
		int p = (m + 1) / 2;
		bool ismirrored = 1, ispalindrome = 1;//set up two bool variables to decide the types of inputstring
		int x, y = 0;
		for (int i = 0; i < p; i++)
		{
			if (inputstr2[i] == inputstr2[m - i - 1])//the determing condition of palindrome string 
			{
				if (reserve(inputstr2[i]) != inputstr2[m - i - 1])//the determing condition of mirrored string 
					ismirrored = 0;		
			}
			else
			{
				ispalindrome = 0;
				if (reserve(inputstr2[i]) != inputstr2[m - i - 1])
					ismirrored = 0;
			}
			
		}
		if (ismirrored == 1 && ispalindrome == 1)//output the right answer
			cout << inputstr << " -- is a mirrored palindrome." << endl<<endl;
		else if (ismirrored == 1 && ispalindrome == 0)
			cout << inputstr << " -- is a mirrored string." << endl << endl;
		else if (ismirrored == 0 && ispalindrome == 1)
			cout << inputstr << " -- is a regular palindrome." << endl << endl;
		else
			cout << inputstr << " -- is not a palindrome." << endl << endl;
	}
		return 0;
}
