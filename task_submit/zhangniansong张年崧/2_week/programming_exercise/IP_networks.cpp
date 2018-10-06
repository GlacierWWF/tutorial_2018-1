/*
 * - File name: IP_network.cpp
 * - Author: Zhang Niansong
 * - Revised: Zhang Niansong
 * - Date: 2018-10-06
 * - Version: 1.0.0
 * - Abstract: A program to find the minimum IP address from inputs, and corresponding mask
 */

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int mask_table[9] = {255, 254, 252, 248, 240, 224, 192, 128, 0};

int main()
{
	int ip[4][1024];
	int m;
	while(scanf("%d",&m)!=EOF)
	{
		memset(ip, 0, sizeof(ip));
		int mask[4];
		int minip[4];
		for(int i=0; i<m; i++)
			scanf("%d.%d.%d.%d",&ip[0][i], &ip[1][i], &ip[2][i], &ip[3][i]);
		for(int i=0; i<4; i++)
		{
			int dif=0, x, j;
			int p,q;
			sort(ip[i], ip[i]+m);
			p = ip[i][m-1];
			q = ip[i][0];
			for(j=1; j<=8; j++)
            {
                if(p%2!=q%2)
                    dif = j;
                p = p/2;
                q = q/2;
            }
			mask[i] = mask_table[dif];
			minip[i] = ip[i][0] & mask[i];
		}
		for(int i=0; i<4; i++)
		{
			if(mask[i] != 255)
			{
				for(i = i+1; i<4; i++)
				{
					mask[i] = 0;
					minip[i] = 0;
				}
				break;
			}
		}
		printf("%d.%d.%d.%d\n",minip[0], minip[1], minip[2], minip[3]);
		printf("%d.%d.%d.%d\n",mask[0], mask[1], mask[2], mask[3]);
	}
	return 0;
}

