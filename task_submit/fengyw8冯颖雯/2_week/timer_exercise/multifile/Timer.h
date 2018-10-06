#ifndef 
#include<ratio>
#include<iomanip>
#include<unistd.h>
#include<string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

using namespace std::chrono; 

//Timer class definition
class Timer
{	
public:
	int open();
	void startTiming();
	void stopTiming();
	void close();
	void pause();
	void resume();
private:
	Mat image;
};
#endif
