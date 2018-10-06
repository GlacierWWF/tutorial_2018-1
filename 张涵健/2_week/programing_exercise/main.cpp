//
//  main.cpp
//  IP
//
//  Created by 张涵健 on 2018/10/6.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int num;
    cin >> num;
    string a[1000];
    int data[1000];
    int max = 0;
    int min = 260;
    int min_ip = 260;
    int point;
    for (int i=0; i<num; i++){
        point = 3;
        cin >> a[i];
        for(int j=0; j<a[i].length(); j++){
            if (a[i][j]=='.') point--;
            if (point==0) {
                data[i]=atoi(a[i].substr(j+1).c_str());
                break;
            }
        }
    }
    for (int i=0; i<num; i++){
        if (data[i]>max){
            max = data[i];
        }
        if (data[i]<min){
            min = data[i];
            min_ip = i;
        }
    }
    string mask = "255.255.255.";
    stringstream ss;
    ss << 255-(max-min)-1 << flush;
    mask = mask + ss.str();
    a[min_ip][a[min_ip].length()-1]--;
    cout << a[min_ip] << endl;
    cout << mask << endl;
    return 0;
}
