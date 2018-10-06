/**************************************************
*                                                 *
*  @file     Address.hpp                          *
*  @brief    Addresss structure header file       *
*                                                 *
*                                                 *
*  @author   atlanswer                            *
*  @email    atlanswer@gmail.com                  *
*  @version  Beta-2                               *
*  @date     2018-10-06                           *
*                                                 *
***************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstdint>

using namespace std;

struct Address {
    //Initializer
    void init(FILE*);
    //Structure data
    uint32_t ipAddress{};
    //Method print
    void print();
};