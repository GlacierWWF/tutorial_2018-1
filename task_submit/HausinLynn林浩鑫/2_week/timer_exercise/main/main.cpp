/********************************************
 *  @file      main.cpp
 *  @brief     implement a timer, interacting
 *			   with user.
 *  
 *-------------------------------------------
 *  Details.
 *-------------------------------------------
 *  @author    HausinLynn
 *  @email     linhx36@mail2.sysu.edu.cn
 *  @version   1.0.0.1
 *  @date      10/03/2018
 *-------------------------------------------
 *
 *-------------------------------------------
 *  Change History:
 *  <date>     | <version> | <author>
 *-------------------------------------------
 *  10/03/2018 | 1.0.0.1   | HausinLynn
 *-------------------------------------------
 *
 *******************************************/

/// System Headers
#include <thread>
#include <mutex>

/// My Header
#include "Timer.hpp"

using namespace std;

/**
 * @brief	timer respond to user's request
 *
 * @param  myTimer	--	a timer need to respond
 *					    to user's request
 * @param  request  --  user's request
 */
void respond(Timer& myTimer, string& request) {
	while (true) {
		getline(cin, request);
		
		/* start timing */
		if (request == "start") {
			myTimer.startTiming();
			cout << "[INFO] Start counting." << endl;
		}
		/* stop timing */
		else if (request == "stop") {
			myTimer.stopTiming();
			cout << "[INFO] Stop counting." << endl;
		}
		/* pause timing */
		else if (request == "pause") {
			myTimer.pause();
			cout << "[INFO] Paused." << endl;
		}
		/* resume timing */
		else if (request == "resume") {
			myTimer.resume();
			cout << "[INFO] Resumed." << endl;
		}
		/* quit program */
		else if (request == "quit") {
			cout << "[INFO] Program exited." << endl;
			break;
		}
		/* error */
		else {
			cout << "[INFO] Command error." << endl;
		}

		request.clear();
	}
}

/**
 * @brief	interactive timer main function
 *
 * @param argc	--	counts of argument
 * @param argv  --  variables of argument
 *
 * @return integer
 */
int main(int argc, char** argv) {
	/* interactive interface */
	cout << "[INFO] Welcome to the counter." << endl;
	cout << "[NOTE] Command: " << endl;
	cout << "\t\t" << "start"  << "\t-----\t" << "start counting"  << endl;
	cout << "\t\t" << "stop"   << "\t-----\t" << "stop counting"   << endl;
	cout << "\t\t" << "pause"  << "\t-----\t" << "pause counting"  << endl;
	cout << "\t\t" << "resume" << "\t-----\t" << "resume counting" << endl;
	cout << "\t\t" << "quit"   << "\t-----\t" << "quit program"    << endl;
	
	/* create timer object */
	Timer myTimer("../images/sysu.jpg");
	myTimer.open();

	/* user's request */
	string request;

	/* let timer's response be a thread */
	thread timer(respond, ref(myTimer), ref(request));
	timer.detach();
	
	/* main thread: continuously output */
	while (request != "quit") {
		myTimer.demoTime();
	}

	myTimer.close();
	return 0;
}
