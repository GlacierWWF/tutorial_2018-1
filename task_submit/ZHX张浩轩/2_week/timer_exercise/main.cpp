#include"Timer.h"
#include<iostream>
#include<string>
#include<thread>
using namespace std;
void choice()
{
    Timer task;
    string choose;
    cout << "[INFO]Welcome! Please input start to start." << endl;
    while(true)
    {
        cin >> choose;
        if(choose == "start")
        {
            thread t(&Timer::startTiming, &task, 0);
            t.detach();
            cout << "[INFO]Start counting." << endl;
        }
        else if(choose == "stop")
        {
            task.stopTiming();
            cout << "[INFO]Stop counting." << endl;
        }
        else if(choose == "pause")
        {
            task.pause();
            cout << "[INFO]Paused." << endl;
        }
        else if(choose == "resume")
        {
            task.resume();
            thread t(&Timer::startTiming, &task, task.get_float());
            t.detach();
            cout << "[INFO]Resumed." << endl;
        }
        else if(choose == "quit")
        {
            task.close();
            cout << "[INFO]Quit." << endl;
            break;
        }
        else
            cout << endl << "Please input useful information." << endl;
    }
}
int main()
{
    Timer task;
    thread tid(choice);
    tid.join();
    return 0;
}