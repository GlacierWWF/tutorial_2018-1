//
//  main.cpp
//  pa
//
//  Created by 湘猪 on 2018/9/29.
//  Copyright © 2018年 湘猪. All rights reserved.
//

#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

char input[999];
const char char1[]="A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {
    " -- is not a palindrome."," -- is a regular palindrome.",
    " -- is a mirrored string."," -- is a mirrored palindrome."
};

char fun(char c){
    if(c>='0'&&c<='9')
        return char1[25+c-'0'];
    else
        return char1[c-'A'];
}

int main(){
    while(cin>>input){
        int len = strlen(input);
        int m = 1,n = 1;
        for(int i = 0;i<(len+1)/2;i++){
            if(input[i]!=input[len-i-1])
                m = 0;
            if(fun(input[i])!=input[len-i-1])
                n = 0;
        }
        cout<<input<<msg[n*2+m]<<endl;
    }
    return 0;
}
