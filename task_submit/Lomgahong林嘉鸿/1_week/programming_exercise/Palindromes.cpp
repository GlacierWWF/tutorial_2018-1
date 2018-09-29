/****************************************************************************************
 *                                                                                      *
 * Copyright (C) 2018 Lomgahong  1073097404@qq.com                                      *
 *                   									*
 * @file	Palindromes.cpp							        *
 * @brief	This programme can recognizes palindromes strings and mirrored strings	*
 * 											*
 * @author	Lomgahong 								*
 * @email	1073097404@qq.com           						*
 * @version	1.0.0 									*
 * @date	2018-09-27								*
 * 											*
 * -------------------------------------------------------------------------------------*
 *   Change History:									*
 *     <Date>    |  <Version>  |   <Author>   |  <Description>                          *
 * -------------------------------------------------------------------------------------*
 *   2018/09/27  |    1.0.0    |  Lomgahong   |  Create file    			*		*
 * -------------------------------------------------------------------------------------*
 *											*
 * 											*
 ****************************************************************************************/

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

bool ds(int);
bool check_pal(string,int);
bool mirror(char,char);
bool check_mir(string,int);

/**
 *@brief	This is the main function.
 *
 *@function	getline(ifstream,string)
 *		check_pal(string,int)
 *		check_mir(string,int)
 *
 *@return	0 means that this function runs correctly.
*/
int main()
{
	//The input data is stored in data.txt 
	ifstream data("data.txt");
	string line,input;
	int len,i;
	if(data)
	{
		//read the data line by line
		while(getline(data,line))
		{
			input=line;
			len=input.length();
			//There are only four conditions:
			if(check_pal(input,len)&&check_mir(input,len))
				cout<<input<<" -- is a mirrored palindromes."<<endl<<endl;
			else if((!(check_pal(input,len)))&&check_mir(input,len))
				cout<<input<<" -- is a mirrored string."<<endl<<endl;
			else if((check_pal(input,len))&&(!(check_mir(input,len))))
				cout<<input<<" -- is a regular palindromes."<<endl<<endl;
			else if((!(check_pal(input,len)))&&(!(check_mir(input,len))))
				cout<<input<<" -- is not a palindrome."<<endl<<endl;
		}
	}
	//output error message while the file is missing	
	else
		cout<<"File not found."<<endl;
	return 0;
}

/**
 * @brief	This function is used to determine whether a number is odd or even.
 *
 * @param	int len:This is the number we need to check.
 *
 * @return	true:If len is odd.
 *		false:If len is even.
 */
bool ds(int len)
{
	//if the length is a odd number:
	if(len%2==1)
		return true;
	//if the length is an even number:
	else
		return false;
}

/**
 * @brief	This function is used to determine whether a string is a palindromes.
 *
 * @param	string input:	This is the string we need to check.
 *		int len:	We use function ds() to determine whether len is odd or even,and determine which way we should use to check the string.
 *		int i:		We use i to count when the for loop is running.
 *		int c:		c=1 means ture,c=0 means false.At the beginning c=1,if there are any error,we break the loop and make c=0.
 *
 * @function	bool ds(int):	We use this fuction to determine whether len is odd or even.
 *
 * @return	true:		If the string is a palindromes.
 *  		false:		If the string is not a palindromes.
 */
bool check_pal(string input,int len)
{
	int i,c=1;
	if(ds(len))
	//if len is odd,the character in the middle of the string doesn't need to be check
	{
		for(i=0;i<((len+1)/2);i++)
		{
			if(input[i]!=input[len-1-i])
			{
				c=0;
				break;
			}
		}
	}
	else
	{
		for(i=0;i<=len/2;i++)
		{
			if(input[i]!=input[len-1-i])
			{
				c=0;
				break;
			}
		}
	}
	//make the final decision
	if(c==1)
		return true;
	else
		return false;
}

/**
 * @brief	This function is used to determine whether two characters are mirrored characters.
 *
 * @param	char c1:	The first character input.
 *		char c2:	The second character input.
 *
 * @return	true:		The two characters are mirrored characters.
 * 		false:		The two characters are not mirrored characters.	
 */  
bool mirror(char c1,char c2)
{
	if(c1=='A'&&c2=='A')
		return true;
	else if((c1=='E'&&c2=='3')||(c1=='3'&&c2=='E'))
		return true;
	else if(c1=='H'&&c2=='H')
		return true;
	else if(c1=='I'&&c2=='I')
		return true;
	else if((c1=='J'&&c2=='L')||(c1=='L'&&c2=='J'))
		return true;
	else if(c1=='M'&&c2=='M')
		return true;
	else if(c1=='O'&&c2=='O')
		return true;
	else if((c1=='S'&&c2=='2')||(c1=='2'&&c2=='S'))
		return true;
	else if(c1=='T'&&c2=='T')
	        return true;
	else if(c1=='U'&&c2=='U')
		return true;
	else if(c1=='V'&&c2=='V')
		return true;
	else if(c1=='W'&&c2=='W')
		return true;
	else if(c1=='X'&&c2=='X')
		return true;
	else if(c1=='Y'&&c2=='Y')
		return true;
	else if((c1=='Z'&&c2=='5')||(c1=='5'&&c2=='Z'))
		return true;
	else if(c1=='1'&&c2=='1')
		return true;
	else if(c1=='8'&&c2=='8')
		return true;
	else
		return false;
}

/**
 * @brief	This function is used to determine whether a string is mirrored.
 *
 * @param	string input:	This is the string wo need to check.
 *		int len:	We use function ds() to determine whether len is odd or even,and determine which way we should use to check the string.
 *		int i:		We use i to count when the for loop is running.*
 *		int c:		c=1 means ture,c=0 means false.At the beginning c=1,if there are any error,we break the loop and make c=0.	
 *
 * @function	bool ds(int):	We use this fuction to determine whether len is odd or even.
 * 		bool mirror(char,char):		We use this function to check mirrored character.
 *
 * @return 	true:		This string is a mirrored string.
 * 		false:		This string is not a mirred string.
 */
bool check_mir(string input,int len)
{
	int i,c=1;
	//if len is odd,the character in the middle of the string doesn't need to be check
	if(ds(len))
	{
		for(i=0;i<(len+1)/2;i++)
		{
			if(!(mirror(input[i],input[len-1-i])))
			{
				c=0;
				break;
			}
		}
		//We should check whether the character in the middle of the string is mirrored.
		//So we used mirror(char,char) and compare this character with itself.
		if(!(mirror(input[(len-1)/2],input[(len-1)/2])))
			c=0;
	}	
	else
	{
		for(i=0;i<=len/2;i++)
		{
			if(!mirror(input[i],input[len-1-i]))
			{
				c=0;
				break;
			}
		}
	}
	//make the final decision
	if(c==1)
		return true;
	else
		return false;
}

