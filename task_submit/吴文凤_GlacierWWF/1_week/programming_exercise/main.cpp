#include <iostream>
#include <stdio.h>
#include <string.h>
//�ο�
#include <ctype.h>

using namespace std;

//�˾�ؼ�����ο���ҳ��Ϣ
//���ַ�˳�����У������Ϲ�����á��ա���ʾ
//λ���ϵ����ݱ���Ӧ������ĸ����
const char* rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
//�ο�
//����ο�λ��
char r(char ch) {
	if (isalpha(ch)) {
		return rev[ch - 'A'];
	}
	return rev[ch - '0' + 25];
}
int main()
{
    char s[50];
    cout<<"Please enter a string:"<<endl;
    gets(s);
    int n=strlen(s);
    int i=0;
    while(s[0]!=' '){
        bool isPalin, ismirrored;
        isPalin=true,ismirrored=true;
        for(i=0;i<(n+1)/2;i++){
            if(s[i]!=s[n-1-i]){
            isPalin=false;}
        }
        for(i=0;i<(n+1)/2;i++){
            if(r(s[i])!=s[n-1-i]){
                ismirrored=false;
            }
        }
        if(isPalin && ismirrored){
            cout<<s<<"-- is a mirrored palindrome."<<endl;
        }
        else if(isPalin && !ismirrored){
            cout<<s<<"-- is a regular palindrome."<<endl;
        }
        else if(!isPalin && ismirrored){
            cout<<s<<"-- is a mirrored string."<<endl;
        }
        else{cout<<s<<"-- is not a palindrome."<<endl;}
    cout<<"Please enter a string:"<<endl;
        gets(s);
        n=strlen(s);
    }
	return 0;
}
