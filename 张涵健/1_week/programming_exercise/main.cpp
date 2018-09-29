//
//  main.cpp
//  Palindromes
//  1.0.0
//  Created by 张涵健 on 2018/9/29.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include <iostream>
using namespace std;

bool mirror(string);
bool palindrome(string);
void check(string);

int main() {
    string a;
    while ( cin >> a)
        check(a);

    return 0;
}

bool mirror(string a){
    char index[1000];
    for(int i = 0; i < 1000; i++){
        index[i] = 0;
    }
    index['A'] = 'A';
    index['E'] = '3';
    index['H'] = 'H';
    index['I'] = 'I';
    index['J'] = 'L';
    index['L'] = 'J';
    index['M'] = 'M';
    index['O'] = 'O';
    index['S'] = '2';
    index['T'] = 'T';
    index['U'] = 'U';
    index['V'] = 'V';
    index['W'] = 'W';
    index['X'] = 'X';
    index['Y'] = 'Y';
    index['Z'] = '5';
    index['1'] = '1';
    index['2'] = 'S';
    index['3'] = 'E';
    index['5'] = 'Z';
    index['8'] = '8';
    for (int i = 0; i < a.length()/2; i++ ){
        if ( a[i] != index[a[a.length()-1-i]]){
            return false;
        }
    }
    if (a.length() % 2 != 0 && a[a.length()/2] != index[a[a.length()/2]])
        return false;

    return true;
}

bool palindrome(string a){
    for (int i = 0; i < a.length()/2; i++){
        if (a[i] != a[a.length()-1-i]){
            return false;
        }
    }
    return true;
}
void check(string a){
    if (palindrome(a)){
        if (mirror(a))
            cout << a << " -- is a mirrored palindrome." << endl << endl;
        else
            cout << a << " -- is a regular palindrome." << endl << endl;
    }
    else{
        if (mirror(a))
            cout << a << " -- is a mirrored string." << endl << endl;
        else
            cout << a << " -- is not a palindrome." << endl << endl;
    }
}
