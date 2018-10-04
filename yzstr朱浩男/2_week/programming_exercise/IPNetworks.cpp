#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string decToBinary(int);
int binaryStringToInt(string);
string binaryStringToAddress(string);

int main()
{
    int times;
    cin >> times;
    int position = 0;
    string originAddress;
    for (int i = 0; i < times; i++)
    {
        char chTmp;
        int b0, b1, b2, b3;

        cin >> b0 >> chTmp >> b1 >> chTmp >> b2 >> chTmp >> b3;
        string address;
        address += decToBinary(b0);
        address += decToBinary(b1);
        address += decToBinary(b2);
        address += decToBinary(b3);

        originAddress = i == 0 ? address : originAddress;

        for (int i = 0; i < 32; i++)
        {
            if (address[i] != originAddress[i])
            {
                position = position < i ? i : position;
                break;
            }
        }
    }
    string startAddress = originAddress;
    string maskAddress;
    for (int i = 0; i < position - 1; i++)
    {
        maskAddress += '1';
    }
    for (int i = position - 1; i < 32; i++)
    {
        startAddress[i] = '0';
        maskAddress += '0';
    }

    cout << binaryStringToAddress(startAddress) << endl;
    cout << binaryStringToAddress(maskAddress) << endl;
}

string decToBinary(int n)
{

    int binaryNum[8];
    for (int i = 0; i < 8; i++)
    {
        binaryNum[i] = 0;
    }

    int i = 0;
    while (n > 0)
    {

        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    string res = "00000000";
    for (int i = 0; i < 8; i++)
    {
        if (binaryNum[8 - i - 1] == 1)
        {
            res[i] = '1';
        }

        else
        {
            res[i] = '0';
        }
    }
    return res;
}

int binaryStringToInt(string s)
{
    int amount = 0;
    for (int i = 0; i < 8; i++)
    {
        if (s[8 - i - 1] == '1')
        {
            amount += pow(2, i);
        }
    }
    return amount;
}

string binaryStringToAddress(string s)
{
    string res;
    res += to_string(binaryStringToInt(s.substr(0, 7)));
    res += '.';
    res += to_string(binaryStringToInt(s.substr(8, 15)));
    res += '.';
    res += to_string(binaryStringToInt(s.substr(16, 23)));
    res += '.';
    res += to_string(binaryStringToInt(s.substr(24, 31)));
    return res;
}