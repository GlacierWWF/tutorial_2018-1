
#ifndef TIMER_CPP


#include "Timer.hpp"

Timer::Timer()
{
    pausePoint = resumePoint;
    isCounting = false;
    Mat img = imread("pic.jpg");
    backGround = img;
}

void Timer::Open()
{
    imshow("Timer", backGround);
    waitkey(0);
}

void Timer::startTiming()
{
    startPoint = std::chrono::high_resolution_clock::now();
    isCounting = true;
    show();
}

void Timer::stopTiming()
{
    imshow("Timer", backGround);
    waitkey(0);
}

void Timer::pause()
{
    pausePoint = std::chrono::high_resolution_clock::now();
    isCounting = false;
    show();
}
float Timer::getDuration()
{
    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - startPoint - (resumePoint - pausePoint);
    return duration.count();
}

void Timer::resume()
{
    resumePoint == std::chrono::high_resolution_clock::now();
    isCounting = true;
    show();
}

void Timer::show()
{
    float lastDuration = 0;
    while (1)
    {
        if (isCounting)
        {

            float duration = getDuration();
            if (duration - lastDuration >= 1)
            {
                cout << setprecision(0) << fixed << duration << endl;
                lastDuration = duration;
            }
            duration = round(duration * 10) / 10.0;
            string durationStr = to_string(duration);
            cout << duration << endl;
            Mat tmpImg = backGround;
            putText(tmpImg, to_string(duration), Point(50, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 23, 0), 4, 8);

            imshow("Timer", tmpImg);
            // Sleep(20);
            waitKey(50);
        }
        else
        {

            imshow("Timer", backGround);
            //Sleep(20);
            waitKey(50);
        }
    }
}

#endif // !TIMER_CPP
