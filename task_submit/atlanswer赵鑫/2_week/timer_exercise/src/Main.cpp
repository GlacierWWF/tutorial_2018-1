
#include "../inc/Timer.hpp"
//! [includes]

extern status action;

int main(int argc, char** argv) {
    Timer timer;
    thread tWindowOpen(bind(&Timer::open, &timer));
    tWindowOpen.detach();

    cout << "[info] Initialization completed, waiting for command:\n"
         << "start - start timing\n"
         << "pause - pause timing\n"
         << "resume - resume timing\n"
         << "quit - quit the timer\n";

    string command{};
    cin >> command;
    if (command == "start") {
        action = sContinue;
        thread tWindowStart(bind(&Timer::startTiming, &timer));
        tWindowStart.detach();

        while (cin >> command) {
            if (command == "pause") {
                thread tWindowPause(bind(&Timer::pause, &timer));
                tWindowPause.join();
            } else if (command == "resume") {
                thread tWindowResume(bind(&Timer::resume, &timer));
                tWindowResume.join();
            } else if (command == "quit") {
                thread tWindowClose(bind(&Timer::close, &timer));
                tWindowClose.join();
                break;
            } else {
                cout << "[info] Not recongnized, try again:\n";
            }
        }
    } else {
        cout << "[info] Not recongnized.\n";
    }
    return 0;
}
