#include "../inc/Timer.hpp"

extern status action;

Timer::Timer() {
    wlcImg = imread(wlcImgUri, IMREAD_COLOR);
    if (wlcImg.empty()) {
        cout << "[Error] Couldn't open or find the image.\n";
    }
    winWidth = wlcImg.cols/2;
    winHeight = wlcImg.rows/2;
}

int Timer::open() {
    namedWindow(wlcWinName, WINDOW_NORMAL);
    resizeWindow(wlcWinName, winWidth, winHeight);

    imshow(wlcWinName, wlcImg);
    waitKey(0);

    return 0;
}

void Timer::startTiming() {
    cout << "[info] Started.\n";
    int timeTerminal{}, count{};
    do {
        Mat wlcImgTmp = wlcImg.clone();
        putText(wlcImgTmp, to_string(timeDelta.count()).substr(0, to_string(timeDelta.count()).find('.') + 2) + " s",
                Point(winWidth/1.7, winHeight),
            FONT_HERSHEY_DUPLEX, 4, Scalar(255), 8);
        imshow(wlcWinName, wlcImgTmp);
        this_thread::sleep_for(100ms);
        timeDelta += chrono::duration<int, deci>(1);
        wlcImgTmp.release();

        if (!(count % 10)) {
            cout << timeTerminal << endl;
            ++timeTerminal;
        }
        ++count;

        switch (action) {
            case sContinue: {
                break;
            }
            case sPause: {
                unique_lock<mutex> lk(mut);
                cout << "[info] Paused.\n";
                cvar.wait(lk, []{return bool(action);});
                cout << "[info] Continued.\n";
                lk.unlock();
                break;
            }
            case sStop: {
                cout << "[info] Quitting.\n";
                destroyWindow(wlcWinName);
                return;
            }
        }
    } while (true);
}

void Timer::pause() {
    action = sPause;
    cvar.notify_one();
    return;
}

void Timer::resume() {
    lock_guard<mutex> lk(mut);
    action = sContinue;
    cvar.notify_one();
    return;
}

void Timer::close() {
    action = sContinue;
    cvar.notify_one();
    action = sStop;
    this_thread::sleep_for(2s);
    return;
}