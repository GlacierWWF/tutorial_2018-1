#include "timer.hpp"

int main()
{
	cout << "---help desk---\n"
		 << "start | stop | pause | resume | quit" << endl;

	Timer tim;
	tim.open("../res/logo.jpg");

	bool isQuit = false;
	while(!isQuit)
	{
		string cmd;
		cin >> cmd;

		if(cmd == "start")
			tim.startTiming();
		else if(cmd == "stop")
			tim.stopTiming();
		else if(cmd == "pause")
			tim.pause();
		else if(cmd == "resume")
			tim.resume();
		else if(cmd == "quit")
			isQuit = true;
	}

	tim.close();

	return 0;
}
