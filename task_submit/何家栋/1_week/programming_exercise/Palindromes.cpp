#include<iostream>
#include<map>
#include<string>
#define NO  " is not a palindrome."
#define MP " is a mirrored palindrome."
#define MS " is a mirrored string."
#define RP " is a regular palindrome."
using namespace std;
map<char, char> match;
void check(string in) {
	int len = in.length();
	int ulen = len - 1;
	int key1 = 1, key2 = 1;
	for (int t = 0; t <= len / 2; t++) {
		if (match.find(in[t])==match.end()||in[ulen - t] != match.at(in[t])) {
			key1 = 0;
		}
		if (in[ulen - t] != in[t]) {
			key2 = 0;
		}
	}
	if (key1&&key2)cout <<in<<" --"<< MP << endl;
	else if (key1 == 1)cout << in << " --" << MS << endl;
	else if (key2 == 1)cout << in << " --" << RP << endl;
	else cout << in << " --" << NO << endl;
}
void setmap() {
	match['A'] = 'A';
	match['E'] = '3';
	match['H'] = 'H';
	match['I'] = 'I';
	match['J'] = 'L';
	match['O'] = 'O';
	match['M'] = 'M';
	match['s'] = '2';
	match['T'] = 'T';
	match['U'] = 'U';
	match['V'] = 'V';
	match['W'] = 'W';
	match['X'] = 'X';
	match['Y'] = 'Y';
	match['Z'] = '5';
	match['L'] = 'J';
	match['1'] = '1';
	match['2'] = 'S';
	match['3'] = 'E';
	match['5'] = 'Z';
	match['8'] = '8';
}
int main() {
	setmap();
	string in;
	while (cin>>in)
	{
		check(in);
	}
	return 0;
}