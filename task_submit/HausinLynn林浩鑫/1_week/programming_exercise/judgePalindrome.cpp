/**************************************
*  @file     judgePalindrome.cpp
*  @brief	 determine the type of
*			 string in file
*  
*--------------------------------------
*  Details.
*--------------------------------------
*  @author   Hausin-Lynn
*  @email    linhx36@mail2.sysu.edu.cn
*  @version  1.0.0.1
*  @date     09/25/2018
*--------------------------------------
*
*--------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>
*--------------------------------------
*  09/25/2018 | 1.0.0.1   | Hausin-Lynn
*--------------------------------------
*
**************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/**
* @brief  type of string
*/
enum str_type{
	not_palindrome		= 0,	/* not palindrome */
	regular_palindrome	= 1,	/* regular palindrome */
	mirrored_string		= 2,	/* mirrored string */
	mirrored_palindrome	= 3,	/* mirrored palindrome */
};


/**
* @brief  determine whether two chars are reversed by each other
* @param  a   --   one input char
* @param  b   --   another input char
*
* @return 
*		 --<false> a and b aren't reversed by each other
*		 --<true> a and b are reversed by each other
*/
bool isReverse(char a, char b);


/**
* @brief  judge type of string
* @param  input_str   --   string to be judged
*
* @return type of input_str
*/
str_type judge(string input_str);


int main() {
	/* get input file */
	string fileName;
	cout << "Please input file name:" << endl;
	cin >> fileName;
	
	/* open file and make sure it exists */
	ifstream inputFile;
	inputFile.open(fileName, ios::in);
	while (!inputFile) {
		// regain the file name while file doesn't exist
		cout << "The file " + fileName;
	    cout <<	" don't exist, please check the file name!" << endl;
		cin >> fileName;
		inputFile.open(fileName, ios::in);
	}
	
	/* get strings in file */
	while (!inputFile.eof()) {
		string input_str;
		inputFile >> input_str;

		/* judge */
		str_type result = judge(input_str);
		
		/* draw a conclusion */
		if (!input_str.empty()) {	// if string not empty
			cout << input_str;
			switch (result) {
				case not_palindrome:
					// not a palindrome
					cout << " -- is not a palindrome.";
					break;
				case regular_palindrome:
					// a regular palindrome
					cout << " -- is a regular palindrome.";
					break;
				case mirrored_string:
					// a mirrored string
					cout << " -- is a mirrored string.";
					break;
				case mirrored_palindrome:
					// a mirrored palindrome
					cout << " -- is a mirrored palindrome.";
					break;
			}
			cout << endl << endl;
		}
	}

	return 0;
}


/*
* isReverse.
* @brief  determine whether a and b are reversed by each other
*
* @return
*        --<false> a and b aren't reversed by each other
*        --<true> a and b are reversed by each other
*/
bool isReverse(char a, char b) {
	bool output;

	switch(a) {
		case 'A':
			output = (b=='A'); break;				/* A -- A */				
		case 'E':
			output = (b=='3'); break;				/* E -- 3 */
		case 'H':
			output = (b=='H'); break;				/* H -- H */
		case 'I':
			output = (b=='I'); break;               /* I -- I */
		case 'J':
			output = (b=='L'); break;				/* J -- L */
		case 'L':
			output = (b=='J'); break;               /* L -- J */
		case 'M':
			output = (b=='M'); break;               /* M -- M */
		case 'O':
			output = (b=='O' || b=='0'); break;     /* O -- O or O -- 0 */
		case 'S':
			output = (b=='2'); break;				/* S -- 2 */
		case 'T':
			output = (b=='T'); break;				/* T -- T */
		case 'U':
			output = (b=='U'); break;				/* U -- U */  
		case 'V':
			output = (b=='V'); break;               /* V -- V */
		case 'W':
			output = (b=='W'); break;				/* W -- W */
		case 'X':
			output = (b=='X'); break;				/* X -- X */
		case 'Y':
			output = (b=='Y'); break;				/* Y -- Y */
		case 'Z':
			output = (b=='5'); break;				/* Z -- 5 */
		case '1':
			output = (b=='1'); break;				/* 1 -- 1 */
		case '2':
			output = (b=='S'); break;				/* 2 -- S */
		case '3':
			output = (b=='E'); break;				/* 3 -- E */
		case '5':
			output = (b=='Z'); break;				/* 5 -- Z */
		case '8':
			output = (b=='8'); break;				/* 8 -- 8 */
		case '0':					
			output = (b=='O' || b=='0'); break;		/* 0 -- O or 0 -- 0 */
		default:
			output = false;
	}

	return output;
}


/*
* judge.
* @brief  judge type of string
*
* @return
*        --<mirrored_palindrome> input_str is a mirrored palindrome
*        --<regular_palindrome> input_str is a regular palindrome
*        --<mirrored_string> input_str is a mirrored string
*        --<not_palindrome> input_str is not a palindrome
*/
str_type judge(string input_str) {
	bool isMirrored = true;
	bool isPalindrome = true;
	
	/* type of input_str */
	str_type output;
	
	/* left side of input_str */
	int left = 0;
	/* right side of input_str */
	int right = input_str.length() - 1;
	
	/* traverse chars from both sides */
	while (left <= right) {
		// not the same
		if (input_str[left] != input_str[right])
			isPalindrome = false;
		
		// not reversed
		if (!isReverse(input_str[left], input_str[right]))
			isMirrored = false;
		
		if (!isMirrored && !isPalindrome)
			break;
		
		/* move index */
		left++;
		right--;	
	}
	
	/* determine the type of input_str */
	if (isPalindrome)
		if (isMirrored)
			output = mirrored_palindrome;
		else
			output = regular_palindrome;
	else
		if (isMirrored)
			output = mirrored_string;
		else
			output = not_palindrome;
	
	return output;	
}
