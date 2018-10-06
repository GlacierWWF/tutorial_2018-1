/**************************************************
*                                                 *
*  @file     Network.hpp                          *
*  @brief    Network class header file            *
*                                                 *
*                                                 *
*  @author   atlanswer                            *
*  @email    atlanswer@gmail.com                  *
*  @version  Beta-2                               *
*  @date     2018-10-06                           *
*                                                 *
***************************************************/

#include <cstdio>
#include <fstream>
#include "Address.hpp"

class Network {
    private:
        int ipNumber{};
        Address* ipAddressList;
        Address networkAddress{};
        Address networkMask{};
        void calculate();
        void printIP(FILE*, Address&);
    public:
        Network(FILE*);
        ~Network();
        void show(FILE*);

        //Test method
        void display();
        Address provide(int);
};