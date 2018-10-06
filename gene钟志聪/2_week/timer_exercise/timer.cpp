#include"timer.hpp"
void Timer::textImage(string text)
{
    Mat tempImage = image.clone();
            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 2;
            int thickness = 2;
            int baseline;   //获取文本框的长宽      
            cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
            Point origin;
            origin.x = image.cols / 2 - text_size.width / 2;
            origin.y = image.rows / 2 + text_size.height / 2;
            cv::putText(tempImage, text, origin, font_face, font_scale, cv::Scalar(0, 0, 0), thickness, 8, 0);
            imshow("timer",tempImage);
    waitKey(1);
}

void Timer::open()
{
    startFlag = false;
    closeFlag = false;
    endFlag = false;
    pauseFlag = false;
    image = imread("/home/gene/welcome.jpg",1);
#ifdef DEBUG
    cout << image;
#endif
    if( !image.data )
    {
        cout << "No image data \n";
        return;
    }
    namedWindow("timer",WINDOW_AUTOSIZE);
    while(startFlag == false)
    {
        imshow("timer",image);
        waitKey(1);
    }
}

void Timer::startTiming()
{
    startFlag = true;
    beg = clock();
    current = clock();
    double currentTime = ( current - beg ) * 1.0 / CLOCKS_PER_SEC;
    int currentIntTime = (int)currentTime;
    while(true)
    {
        if( pauseFlag == true )
        {
            continue;
        }
        if( endFlag == true )
        {
            return;
        }
        if( stopFlag == true )
        {
            break;
        }
        current = clock();
        currentTime = ( current - beg ) * 1.0 / CLOCKS_PER_SEC;
        if(((int)currentTime) - currentIntTime > 1 )
        {
            currentIntTime++;
            cout << currentIntTime+1 << endl;
        }
        textImage(to_string((int)(currentTime*10)*1.0/10)+"s");

    }
    startFlag = false;
}
void Timer::stopTiming()
{
    startFlag = false;
    stopFlag = true;
    while(closeFlag == false && startFlag == false )
    {
        imshow("timer", image);
        waitKey(1);
    }
    stopFlag = false;
}

void Timer::close()
{
    closeFlag = true;
    destroyWindow("timer");
}

void Timer::pause()
{
    pauseFlag = true;
}

void Timer::resume()
{
    beg = beg + clock() - current;
    current = clock();
    pauseFlag = false;
}
bool Timer::startFlag = false;
bool Timer::closeFlag = false;
bool Timer::endFlag = false;
bool Timer::pauseFlag = false;
clock_t Timer::beg = 0;
clock_t Timer::current = 0;
Mat Timer::image;
bool Timer::stopFlag = false;

