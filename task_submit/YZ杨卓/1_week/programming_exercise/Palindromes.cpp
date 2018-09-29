//Author: 杨卓
//Date: 2018-09-29
//Version: 1.0.0
//Abstract: 判断输入字符串是否为回文串或者镜像字符串

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

bool mir(char str[21]);
bool pal(char str[21]);
void judge();

int main()
{
        int flag = 0;

        while(1)
        {
                cout << "输入 1 为输入字符串，输入其他数字为退出程序" << endl;
                cin >> flag;
                if(flag == 1)
                        judge();

                else
                        break;
        }

        return 0;
}

// 判断输入，并输出结果
void judge()
{
        bool is_pal = true;
        bool is_mir = true;

        char str[21] = {0};
        cin >> str;

        is_pal = pal(str);
        is_mir = mir(str);

        if(is_pal == true && is_mir == true)
                cout << str << " -- is a mirrored palindrome." << endl;

        else if(is_pal == true && is_mir == false)
                cout << str << " -- is a regular palindrome." << endl;

        else if(is_pal == false && is_mir == true)
                cout << str << " -- is a mirrored string." << endl;

        else
                cout << str << " -- is not a palindrome." << endl;

}


//判断是否为回文字符串
bool pal(char str[21])
{
        bool flag_pal = true;
        int len = 0;
        len = strlen(str);

        for(int i=0; i<len/2 ; i++)
        {
                if(str[i] != str[len-i-1])
                {
                        flag_pal = false;
                        break;
                }

        }


        return flag_pal;
}

//判断是否为镜像字符串
bool mir(char str[21])
{
        bool flag_mir = true;
        int len = 0;
        len = strlen(str);

        char mirror[200] = {0};

        mirror['A'] = 'A';       mirror['E'] = '3';
        mirror['H'] = 'H';       mirror['I'] = 'I';
        mirror['J'] = 'L';       mirror['L'] = 'J';
        mirror['M'] = 'M';       mirror['O'] = 'O';
        mirror['S'] = '2';       mirror['T'] = 'T';
        mirror['U'] = 'U';       mirror['V'] = 'V';
        mirror['W'] = 'W';       mirror['X'] = 'X';
        mirror['Y'] = 'Y';       mirror['Z'] = '5';
        mirror['1'] = '1';       mirror['2'] = 'S';
        mirror['3'] = 'E';       mirror['5'] = 'Z';
        mirror['8'] = '8';

        for(int i=0 ; i<len/2 ;i++)
        {
                if(mirror[str[i]] != str[len-1-i] )
                {
                        flag_mir = false;
                        break;
                }

        }

        return flag_mir;
}

























































