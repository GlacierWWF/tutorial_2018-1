//Author: zhanghaohuan
//Date: 2018-9-29
//Abstract: Palindromes

#include <iostream>
#include <cstring>
using namespace std;

int main() 
{
  char c[100];
  while(scanf("%s", c) != EOF)
  {
    bool flag_pal = 1, flag_mir = 1;
    int n = strlen(c);
    for(int i = 0; i < n; i++)
    {
      if(c[i] != c[n - i - 1])
        flag_pal = 0;
      if(c[i] == 'A' || c[i] == 'H' || c[i] == 'I' || c[i] == 'M' || c[i] == 'O'	                  || c[i] == 'T' || c[i] == 'U' || c[i] == 'V' || c[i] == 'W'
		     || c[i] == 'X' || c[i] == 'Y' || c[i] == '1' || c[i] == '8')
        continue;
      else if((c[i] == 'E' && c[n - i - 1] == '3') ||
              (c[i] == 'J' && c[n - i - 1] == 'L') ||
	      (c[i] == 'L' && c[n - i - 1] == 'J') ||
	      (c[i] == 'S' && c[n - i - 1] == '2') ||
	      (c[i] == 'Z' && c[n - i - 1] == '5') ||
	      (c[i] == '2' && c[n - i - 1] == 's') ||
	      (c[i] == '3' && c[n - i - 1] == 'E') ||
	      (c[i] == '5' && c[n - i - 1] == 'Z') )
	      continue;
      else
        flag_mir = 0;
    }
    if(flag_pal && flag_mir)
      printf("%s -- is a mirrored palindrome.\n\n", c);
    else if(flag_pal && !flag_mir)
      printf("%s -- is a regular palindrome.\n\n", c);
    else if(!flag_pal && flag_mir)
      printf("%s -- is a mirrored string.\n\n", c);
    else 
      printf("%s -- is not a palindrome.\n\n", c);

  }
  return 0;
}
