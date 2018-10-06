/* Title: main.cpp
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-10-06
 * Version: 1.0.0
 * Main program to handle I/O of timer and calls Timer class
 */

#include <thread>
#include <mutex>
#include "Timer.hpp"
using namespace std;

/*
 * @ brief function that handles input
 * @ Detail
 * This function starts in an independent thread that keeps reading
 * input from user and performs corresponding actions.
 */
void input(Timer& timer, string& request) {
	while (true) {
		getline(cin, request);
		
		if (request == "start") {
			timer.startTiming();
			cout << "[INFO] Start counting." << endl;
		}

		else if (request == "stop") {
			timer.stopTiming();
			cout << "[INFO] Stop counting." << endl;
		}

		else if (request == "pause") {
			timer.pause();
			cout << "[INFO] Paused." << endl;
		}

		else if (request == "resume") {
			timer.resume();
			cout << "[INFO] Resumed." << endl;
		}

		else if (request == "quit") {
			cout << "[INFO] Program exited." << endl;
			break;
		}

		else {
			cout << "[INFO] Undefined Command." << endl;
		}

		request.clear();
	}
}


int main(int argc, char** argv) {

	cout << "[INFO] Welcome to the counter." << endl;
	Timer timer("Mojave.jpg");
	timer.open();
	string request;
	thread Timer(input, ref(timer), ref(request));
	Timer.detach();
	
	while (request != "quit") {
		timer.run();
	}

	timer.close();
	return 0;
}