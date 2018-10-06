#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int table[9] = {255, 254, 252, 248, 240, 224, 192, 128, 0};
int main(){
	int ip[4][1024], m;
	while(scanf("%d",&m)!=EOF){
		memset(ip, 0, sizeof(ip));
		int zwym[4];
		int ip_min[4];
		for(int i=0; i<m; i++)
			scanf("%d.%d.%d.%d",&ip[0][i], &ip[1][i], &ip[2][i], &ip[3][i]);
		for(int i=0; i<4; i++){
			int dif=0, x, j;
			int p,q;
			sort(ip[i], ip[i]+m);
			p = ip[i][m-1];
			q = ip[i][0];
			for(j=1; j<=8; j++){
                if(p%2!=q%2)
                    dif = j;
                p = p/2;
                q = q/2;
            }
			zwym[i] = table[dif];
			ip_min[i] = ip[i][0] & zwym[i];
		}
		for(int i=0; i<4; i++){
			if(zwym[i] != 255){
				for(i = i+1; i<4; i++){
					zwym[i] = 0;
					ip_min[i] = 0;
				}
				break;
			}
		}
		printf("%d.%d.%d.%d\n",ip_min[0], ip_min[1], ip_min[2], ip_min[3]);
		printf("%d.%d.%d.%d\n",zwym[0], zwym[1], zwym[2], zwym[3]);
	}
	return 0;
}

