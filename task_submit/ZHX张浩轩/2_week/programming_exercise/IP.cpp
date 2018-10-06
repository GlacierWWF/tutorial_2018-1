/*
张浩轩
2018-10-05
IP网络地址练习题
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int str_int(string);//string to int
int find_m(vector<int> &, int);//find min or max in a vector
int find_bin(int);//find times about a int number divided by 2

int main()
{
    int n;
    cout << "[INFO]Input number:" << endl;
    cin >> n;
    vector<string> strs(n, "");
    int i, j, k, min, max;
    for(i = 0; i < strs.size(); i++)
    {
        cout << "[INFO]Input IP:" << endl;
        cin >> strs[i];    
    }
    int dot;
    string temp = "";
    vector<int> count;
    for(i = 0; i < n; i++)
    {
        dot = 0;
        for(j = 0; j < strs[i].length(); j++)
        {
            if(strs[i][j] == '.')
                dot++;
            if(dot == 3)
            {
                dot = j + 1;
                while(dot < strs[i].length())
                {
                    temp += strs[i][dot];
                    dot++;
                }
                break;
            }
        }
        count.push_back(str_int(temp));
        temp.clear();
    }
    min = find_m(count, 0);
    max = find_m(count, 1);
    int cha = max - min + 1;
    int min_bin = find_bin(cha);
    cha = 1;
    for(i = 0; i < min_bin; i++)
        cha *= 2;
    min = max - cha + 1;
    dot = 0;
    cout << endl << "[INFO]Output:" << endl;
    for(i = 0; i < strs[0].length(); i++)
    {
        cout << strs[0][i];
        if(strs[0][i] == '.')
            dot++;
        if(dot == 3)
            break;
    }
    cout << min << endl;
    cout << "255.255.255." << 256 - cha << endl;
    return 0;
}

int str_int(string str)
{
    int number = 0, chengshu = 1;
    int i;
    for(i = 0; i < str.length() - 1; i++)
    {
        chengshu *= 10;
    }
    for(i = 0; i < str.length(); i++)
    {
        number += chengshu * (str[i] - '0');
        chengshu /= 10;
    }
    return number;
}

int find_m(vector<int> &temp, int n)
{
    int min = temp[0], max = temp[0];
    int i;
    for(i = 0; i < temp.size(); i++)
    {
        if(min > temp[i])
            min = temp[i];
        if(max < temp[i])
            max = temp[i];
    }
    return n == 0 ? min: max;
}

int find_bin(int number)
{
    int count;
    if(number % 2 == 0)
        count = -1;
    else if(number == 1)
        return 0;
    else
        count = 0;
    while(number != 0)
    {
        number /= 2;
        count++;
    }
    return count;
}