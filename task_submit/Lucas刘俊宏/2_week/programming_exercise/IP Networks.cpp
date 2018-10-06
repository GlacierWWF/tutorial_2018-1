//
//  main.cpp
//  IP Networks for SYSU-IARC
//
//  Week 2 project: IP Networks.
//
//  @author    liujunhong
//  @email    290315614@qq.com
//  @version    1.0.0.0
//  @date    2018/9/30
//  Copyright © 2018年 liujunhong. All rights reserved.
//

#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<math.h>
using namespace std;
int IP[100][5];
int IP2[100][4][9];   //IP的二进制形式
int main(int argc, const char * argv[])
{
    int task;
    while(scanf("%d", &task) != EOF)   //输入IP地址的个数
    {
        for (int i = 0; i < task; i++)
        {
            scanf("%d.%d.%d.%d", &IP[i][0], &IP[i][1], &IP[i][2], &IP[i][3]);    //完成输入IP地址
        }
        //将十进制的IP地址转化为二进制，并存储在IP2数组里
        for (int i = 0; i < task; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 8; k++)
                    {
                        IP2[i][j][7 - k] = (IP[i][j] & (1 << k) ? 1 : 0);
                    }
        //  通过每一位的比较来确定n的值
        int flag = 1;   //当flag = 0，标志着退出所有循环
        int i,j,k = 0;
        for(j = 0;j < 4;j++)
        {
            for(k = 0;k < 8;k++)
            {
                for(i = 0;i < task - 1;i++)
                {    
                    if((int*)IP2[i][j][k] != (int*)IP2[i+1][j][k])
                    {
                        flag = 0;
                        break;
                    }
                }
            if(flag == 0)
                break;
            }
        if(flag == 0)
            break;
        }
        //int 两个数组用来储存ip地址和子网掩码的二进制形式
        int ans_ip2[4][8];
        int ans_ym2[4][8];
        //全部置为零
        memset(ans_ip2, 0, sizeof(ans_ip2));
        memset(ans_ym2, 0, sizeof(ans_ym2));
        //最小IP即，二进制前32-n位与其他IP一致，后n位全为0
        for(int jj = 0;jj < j;jj++)
        {
            for(int kk = 0;kk < 8;kk++)
            {
                ans_ip2[jj][kk] = IP2[0][jj][kk];
            }
        }
        
        for(int jj = 0;jj < k;jj++)
        {
            ans_ip2[j][jj] = IP2[0][j][jj];
        }
        //子网掩码是二进制前32-n位为1，后n位全为0
        for(int jj = 0;jj < j;jj++)
        {
                for(int kk = 0;kk < 8;kk++)
                {
                    ans_ym2[jj][kk] = 1;
                }
        }
        for(int jj = 0;jj < k;jj++)
        {
            ans_ym2[j][jj] = 1;
        }
        /*
        //输出ip地址
        for(int jj = 0;jj < 4;jj++)
            for(int kk = 0;kk < 8;kk++)
            {
                cout << ans_ip[jj][kk];
                if(jj != 3 && kk == 7)
                    cout << '.';
            }
        cout << endl;
        //输出子网掩码
        for(int jj = 0;jj < 4;jj++)
            for(int kk = 0;kk < 8;kk++)
            {
                cout << ans_ym[jj][kk];
                if(jj != 3 && kk == 7)
                    cout << '.';
            }
        cout << endl;
        */
        //将二进制转为十进制
        int ans_ip[4] = {0};
        int ans_ym[4] = {0};
        int kk = 0;
        for(int ii = 0;ii < 4;ii++)
        {
            for(int jj = 0;jj < 8;jj++)
            {
                ans_ip[kk] += ans_ip2[ii][jj] * pow(2,7 - jj);
            }
            kk++;
        }
        kk = 0;
        for(int ii = 0;ii < 4;ii++)
        {
            for(int jj = 0;jj < 8;jj++)
            {
                ans_ym[kk] += ans_ym2[ii][jj] * pow(2,7 - jj);
            }
            kk++;
        }
        //将ip地址和子网掩码输出
        for(int ii = 0;ii < 4;ii++)
        {
            cout << ans_ip[ii];
            if(ii != 3)
                cout << '.';
        }
        cout << endl;
        for(int ii = 0;ii < 4;ii++)
        {
            cout << ans_ym[ii];
            if(ii != 3)
                cout << '.';
        }
    }
    return 0;
}
