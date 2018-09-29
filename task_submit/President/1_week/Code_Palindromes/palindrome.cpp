/*********************************************************
 * Palindrome for SYSU-IARC
 *
 * Week 1 project: Palindrome.
 *
 * This file is an example for freshmen to understant
 * how to code in correct format with annotation.
 *
 * @author	Champion.Liu
 * @email	liuyinyi@vip.qq.com
 * @version	1.0.0.0
 * @date	2018/9/29
 */

/// System Headers
#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

/**
 * @brief Palin Enum Constant
 */
namespace Palin
{
	enum StrType {NOTHING, REGULAR_PALIN, MIRRORED, MIRRORED_PALIN};
}

/**
 * @brief reverse mirror look-up map
 */
const std::map<char, char> check_map {
	{'A', 'A'}, {'E', '3'}, {'H', 'H'}, {'I', 'I'}, {'J', 'L'}, {'L', 'J'},
	{'M', 'M'}, {'O', 'O'}, {'S', '2'}, {'T', 'T'}, {'U', 'U'}, {'V', 'V'},
	{'W', 'W'}, {'X', 'X'}, {'Y', 'Y'}, {'Z', '5'}, {'1', '1'}, {'2', 'S'},
	{'3', 'E'}, {'5', 'Z'}, {'8', '8'}
};

/**
 * @brief reverse mirror match function
 *
 * @param a		compared char A
 * @param b		compared char B
 * @param fm	finding map
 *
 * @return bool	whether matches or not
 */
bool match(char a, char b, const std::map<char, char>& fm)
{
	auto search = fm.find(a);
	if(search != fm.end())
	{
		if(search->second == b)
			return true;
	}
	return false;
}

/**
 * @brief judge if it is palindrome / mirrored string
 *
 * @param txt	input testing string
 *
 * @return Palin::StrType	which type to match
 */
Palin::StrType judge(const string& txt)
{
	bool 
		pflag = true,	//!< palindrome flag
		mflag = true;	//!< mirrored flag
	auto len = txt.length();
	for(auto i = 0; i < floor(len/2); i++)
	{
		auto j = len - i - 1;
		if(txt.at(i) != txt.at(j))
			pflag = false;
		if(!match(txt.at(i), txt.at(j), check_map))
			mflag = false;
	}

	if(pflag && mflag)
		return Palin::MIRRORED_PALIN;
	else if(!pflag && mflag)
		return Palin::MIRRORED;
	else if(pflag && !mflag)
		return Palin::REGULAR_PALIN;
	else
		return Palin::NOTHING;
}

/**
 * @brief Palindrome Main Function
 *
 * @param argc		counts of argument
 * @param argv		variables of argument
 *
 * @return integer
 */
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "[usage] palin <judge_text_without_space>" << endl;
		return -1;
	}
		
	string txt = argv[1];
	Palin::StrType st = judge(txt);

	switch(st)
	{
		case Palin::NOTHING:
			cout << txt << " -- is not a palindrome." << endl;
			break;
		case Palin::REGULAR_PALIN:
			cout << txt << " -- is a regular palindrome." << endl;
			break;
		case Palin::MIRRORED:
			cout << txt << " -- is a mirrored string." << endl;
			break;
		case Palin::MIRRORED_PALIN:
			cout << txt << " -- is a mirrored palindrome." << endl;
			break;
	}

	return 0;
}
