#include <iostream>
//Using std namespace
using namespace std;

//Global constants
enum STAT{NP, RP, MS, MP};
const string DESCRIPTION[]{" -- is not a palindrome.",         //The string is not a palindrome and is not a mirrored string
                           " -- is a regular palindrome.",     //The string is a palindrome and is not a mirrored string
                           " -- is a mirrored string.",        //The string is not a palindrome and is a mirrored string
                           " -- is a mirrored palindrome."};   //The string is a palindrome and is a mirrored string
const char MIRROR[]{'0', '1', 'S', 'E', '0', 'Z', '0', '0', '8', '0',   //Number 0~9
                    '0', '0', '0', '0', '0', '0', '0',                  //ASCII 58~64
                    'A', '0', '0', '0', '3', '0', '0', 'H', 'I', 'L',   //Character A~J
                    '0', 'J', 'M', '0', 'O', '0', '0', '0', '2', 'T',   //Character K~T
                    'U', 'V', 'W', 'X', 'Y', '5'};                      //Character U~Z

int main() {
    //The string to be checked
    string str{};
    //Loop every input line
    while (cin >> str) {
        //Initicial condition
        bool isPatlindrome{true}, isMirrored{true};
        STAT KIND{};

        for (int index{0}; index < (str.size() - index - 1); ++index) {
            //Check if it's a patlindrome
            if (str[index] != str[str.size() - index - 1])
                isPatlindrome = false;
            //Check if it's mirrored
            if (str[str.size() - index - 1] != MIRROR[str[index] - '0'])
                isMirrored = false;
            /*Since the input string is short (no more than 20 characters),
              we just check all the characters without any break conditions.*/
        }
        //Convert to enum type
        KIND = STAT(isPatlindrome + isMirrored * 2);
        //Output
        cout << str << DESCRIPTION[KIND]
             << endl << endl;   //An empty line followed
    }

    return 0;
}