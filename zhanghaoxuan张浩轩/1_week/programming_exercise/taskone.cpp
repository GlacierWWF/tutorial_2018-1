#include<iostream>
#include<string>
using namespace std;
string reverse_str(string str);
bool if_padlindrome(string str);
bool if_mirror(string str);

int main()
{
    string str;
    bool pad;
    bool mir;
    while(true)
    {
        cout << "[INFO] Input your string, quit to exit." << endl;
        cin >> str;
        if(str == "quit" || str == "QUIT")
            break;
        pad = if_padlindrome(str);
        mir = if_mirror(str);
        cout << str;
        if(!pad && !mir)
            cout << " -- is not a palindrome.";
        else if(pad && !mir)
            cout << " -- is a regular palindrome.";
        else if(!pad && mir)
            cout << " -- is a mirrored string.";
        else 
            cout << " -- is a mirrored palindrome.";

        cout << endl << endl;
    }
    return 0;
}

string reverse_str(string str)
{
    int length = str.length();
    string temp = "";
    int i;
    for(i = length - 1; i >=0; i--)
        temp += str[i];
    return temp;
}
bool if_padlindrome(string str)
{
    if(str == reverse_str(str))
        return true;
    return false;
}
bool if_mirror(string str)
{
    string temp = "";
    char letter, re_letter;
    int length = str.length();
    int i;
    for(i = 0; i < length; i++)
    {
        re_letter = '*';
        letter = str[i];
        switch(letter)
        {
            case 'E':
            re_letter = '3';
            break;
            case 'J':
            re_letter = 'L';
            break;
            case 'L':
            re_letter = 'J';
            break;
            case 'S':
            re_letter = '2';
            break;
            case 'Z':
            re_letter = 'Z';
            break;
            case '2':
            re_letter = 'S';
            break;
            case '3':
            re_letter = 'E';
            break;
            case '5':
            re_letter = 'Z';
            break;
        }
        if(letter == 'A' || letter == 'H' || letter == 'I' || letter == 'M' || letter == 'O'
        || letter == 'T' || letter == 'U' || letter == 'V' || letter == 'W' || letter == 'X' 
        || letter == 'Y' || letter == '1' || letter == '8')
            re_letter = letter;
        if(re_letter == '*')
            return false;
        temp += re_letter;
    }
    if(temp == reverse_str(str))
        return true;
    return false;
}