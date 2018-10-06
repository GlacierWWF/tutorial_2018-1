//This program is  used to find the smallest possible IP network
//the main method is to change decimal to binary
#include <iostream>
#include <cstdio>
using namespace std;
//底数为2的幂函数，递归法
int power2(int n){
    int sum;
    if(n==0){sum=1;}
    else{sum=2*power2(n-1);}
    return sum;
}
int main()
{
    char addexm[1000][32];//将行数最大化
    int num;//要测验的IP地址的个数
    int i,j;
//数组初始化
   for(i=0;i<1000;i++){
        for(j=0;j<32;j++){
            addexm[i][j]='0';
        }
    }
    cout<<"Enter the number of IP addresses(0~1000):";
    int comtem[2][4];//一个暂时存放四个十进制数及最后结果的数组
//初始化
    for(i=0;i<2;i++){
        for(j=0;j<4;j++){
            comtem[i][j]=0;
        }
    }
//输入各个IP地址
    int k,temp,t;
    while(scanf("%d",&num)!=EOF){
    for(k=0;k<num;k++){
        //以特定的格式输入IP地址
        scanf("%d.%d.%d.%d",&comtem[0][0],&comtem[0][1],&comtem[0][2],&comtem[0][3]);
        //十进制数转化为二进制数，用字符型0和1来标记表示二进制数，并储存在addexm数组中
        for(i=0;i<4;i++){
                temp=comtem[0][i];
                for(j=((i+1)*8-1);j>=i*8;j--){
                    if(temp%2==0){addexm[k][j]='0';}
                    else{addexm[k][j]='1';}
                    temp=temp/2;
//测试                    cout<<addexm[k][j];
                }
//测试               cout<<endl;
        }
//测试        for(t=0;t<32;t++){cout<<addexm[k][t];}
    }
//比较IP地址
    int rec,trec;//记录第一个不同的数的位置
    for(k=0;k<num-1;k++){
        for(i=k+1;i<num;i++){
            for(j=0;j<32;j++){
                if(addexm[k][j]!=addexm[i][j]){trec=j+1;break;}
            }
        if(trec<rec){rec=trec;}
        }
    }
//测试    cout<<rec<<endl;
    int smallest[2][32];
    for(i=0;i<2;i++){
        for(j=0;j<32;j++){
            smallest[i][j]=0;
        }
    }
//设置最小的IP地址
    for(i=0;i<rec;i++){
        if(addexm[0][i]!='0'){smallest[0][i]=1;}
    }
    for(j=0;j<4;j++){
        comtem[0][j]=0;
        for(i=j*8;i<(j+1)*8;i++){
        comtem[0][j]=comtem[0][j]+smallest[0][i]*power2((j+1)*8-i-1);
        }
    }
//设置子网掩码
    for(j=0;j<rec;j++){
        smallest[1][j]=1;
    }
    for(j=0;j<4;j++){
        comtem[1][j]=0;
        for(i=j*8;i<(j+1)*8;i++){
        comtem[1][j]=comtem[1][j]+smallest[1][i]*power2((j+1)*8-i-1);
        }
    }
//输出结果
    cout<<comtem[1][0]<<"."<<comtem[1][1]<<"."<<comtem[1][2]<<"."<<comtem[1][3]<<endl;
    cout<<comtem[0][0]<<"."<<comtem[0][1]<<"."<<comtem[0][2]<<"."<<comtem[0][3]<<endl;
    }
    return 0;
}

