#include "SSD.hpp"

enum situation{normal, blurry, overexpose};

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

class SSD2 {
    private:
        SSD0 *Img1, *Img2;
        cv::Mat combineArm;
        void condense();
        void amalgamate();
    
    public:
        SSD2(char*);
        SSD2(char*, char*);
        void readDigit();
};