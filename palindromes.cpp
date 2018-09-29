#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
bool palindrome =false ;
bool mirrored =false ;
char word[1000];
cin >> word;

int x= strlen(word);
int y= strlen(word)-1;

for ( int a=0; a<x; a++)
{
if (word [a] == word [y-a] )
{
palindrome = true;
}
}
for ( int c=0; c<x; c++)
{
switch (word [c])
{
case 'A': return 'A';
case 'E': return '3';
case 'H': return 'H';
case 'I': return 'I';
case 'J': return 'L';
case 'M': return 'M';
case 'O': return 'O';
case 'S': return '2';
case 'T': return 'T';
case 'U': return 'U';
case 'V': return 'V';
case 'W': return 'W';
case 'X': return 'X';
case 'Y': return 'Y';
case 'Z': return '5';
case 'B': return 'C';
case 'C': return 'D';
case 'D': return 'F';
case 'F': return 'G';
case 'G': return 'K';
case 'K': return 'N';
case 'N': return 'P';
case 'P': return 'P';
case 'Q': return 'R';
case 'R': return 'B';
}
if (word [c] == word [y-c])
{
mirrored = true;
}
}

if (palindrome == true && mirrored==false)
{
cout << "is a palindrome " << "\n";
}

if(mirrored== true && palindrome==false)
{
cout << "is a mirrored string" << "\n";
}

if (palindrome == true && mirrored == true)
{
cout << "is a mirrored palindrome" << "\n";
}

if (palindrome == false && mirrored == false)
{
cout << "is not a palindrome" << "\n";
}

return 0;

}

