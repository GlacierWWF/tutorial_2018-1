//
//  main.cpp
//  Digit_discern
//
//  Created by 张涵健 on 2018/10/8.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

//#include "client.hpp"

#include "../include/client.hpp"

int main(int argc, char * argv[])
{
    client test;
    string name ;
    string name2;
    if(argc == 3){
        name = argv[1];
        name2 = argv[2];
        test.test_3(name, name2);
    }
    else if(argc == 2){
        name = argv[1];
        test.open(name);
        test.test();
    }

    cout << endl;
    return 0;
}


