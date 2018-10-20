/*****************************************************************************
*  Seven-segment display ocr program                                         *
*                                                                            *
*  @file     main.cpp                                                        *
*  @brief    Main source file for testing program                            *
*                                                                            *
*  @author   atlanswer                                                       *
*  @email    atlanswer@gmail.com                                             *
*  @version  Beta-2                                                          *
*  @date     10/20/2018                                                      *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/10/20 | Beta-2   | atlanswer      | Complete mission                 *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "SSD2.hpp"

int main(int argc, char** argv) {
    if (argc == 1 or argc > 3) {
        std::cout << "usage: ./ocr <image_path>" << std::endl;
        std::cout << "Argument number: " << argc - 1 << std::endl;
        return -1;
    }

    if (argc == 2) {
        SSD2 ONE_FUCKING_UNREADABLE_IMAGE(argv[1]);
    } else {
        SSD2 THE_MOTHER_OF_TWO_FUCKING_BLURRY_IMAGES(argv[1], argv[2]);
        THE_MOTHER_OF_TWO_FUCKING_BLURRY_IMAGES.readDigit();
    }

    return 0;
}