/**************************************************
*                                                 *
*  @file     Timer.hpp                            *
*  @brief    Timer class header file              *
*                                                 *
*                                                 *
*  @author   atlanswer                            *
*  @email    atlanswer@gmail.com                  *
*  @version  Beta-2                               *
*  @date     2018-10-06                           *
*                                                 *
***************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace cv;
using namespace std;
using decisecond = chrono::duration<float, ratio<1>>;

extern decisecond timeDelta;
extern bool doNotTiming;
enum status{sPause, sContinue, sStop};
extern mutex mut;
extern condition_variable cvar;

class Timer {
    private:
        string wlcImgUri{"./res/background.jpg"};
        string wlcWinName{"Timer!"};
        int winWidth{};
        int winHeight{};
        Mat wlcImg;

    public:
        Timer();
        int open();
        void startTiming();
        void pause();
        void resume();
        void stopTiming();
        void receiveCommand();
        void close();
};