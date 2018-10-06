/**************************************************
*                                                 *
*  @file     Address.cpp                          *
*  @brief    Addresss structure source file       *
*                                                 *
*                                                 *
*  @author   atlanswer                            *
*  @email    atlanswer@gmail.com                  *
*  @version  Beta-2                               *
*  @date     2018-10-06                           *
*                                                 *
***************************************************/

#include "Address.hpp"

void Address::init(FILE* ipAddresses) {
    for (int i{24}; i >= 0; i -= 8) {
        uint32_t byte{};
        fscanf(ipAddresses, "%*[^0-9]%3d[^0-9]", &byte);
        ipAddress += (byte << i);
    }
}

void Address::print() {
    printf("%u", ipAddress);
}