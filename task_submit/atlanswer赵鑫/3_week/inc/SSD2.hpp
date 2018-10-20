/*****************************************************************************
*  Seven-segment display ocr program                                         *
*                                                                            *
*  @file     SSD2.hpp                                                        *
*  @brief    SSD2 class header file                                          *
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

#include "SSD.hpp"

//---------------------------------------------------------------------------
// Platform Defines
//---------------------------------------------------------------------------
enum situation{normal, blurry, overexpose};

/**
    * @brief Class for dealing with one of two separate images
    */
class SSD0 {
    private:
        situation imgType;
        int histMax;

        void histAnalysis(cv::Mat&);
    
    public:
        cv::Mat oImg;
        cv::Mat eImg;
        SSD0(char*);
        cv::RotatedRect extract();
        cv::Mat transform;
};


/**
    * @brief Class for processing two images input
    */
class SSD2 {
    private:
        SSD0 *Img1, *Img2;
        SSD* Img3;
        cv::Mat combineArm;
        void condense();
        void amalgamate();
    
    public:
        SSD2(char*);
        SSD2(char*, char*);
        void readDigit();
};