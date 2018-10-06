#include<iostream>

#include"Timer.h"

using namespace std;

int main(void)
{
		int b;

		cout << "请输入倒计时秒数（以毫秒记）";
		cin >> b;

		Timer tHello([]()
        {
		       cout << "." << endl;
	    });

		tHello.setSingleShot(false);
		tHello.setInterval(Timer::Interval(1000));
		tHello.start(true);

		Timer tStop([&]()
		{
		     tHello.stop();
		});

		tStop.setSingleShot(true);
		tStop.setInterval(Timer::Interval(b));
		tStop.start();

		return 0;
}

