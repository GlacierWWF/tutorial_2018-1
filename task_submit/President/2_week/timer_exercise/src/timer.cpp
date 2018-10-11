#include "timer.hpp"

const char* WIN_TITLE = "TIMER WINDOW";

Timer::Timer():
	_flag(false)
{
}

/////////////////////////////

using namespace std::placeholders;

bool Timer::open(string path)
{
	if(_flag)
		return false;

	img = imread(path);
	if(!img.data)
		return false;

	nowFunc = std::bind(&Timer::free, this, _1);
	namedWindow(WIN_TITLE, 0);

	_flag = true;
	_thr = std::thread(&Timer::timThread, this);
	return true;
}

void Timer::close()
{
	stopTiming();
	_flag = false;
	_thr.join();
}

void Timer::startTiming()
{
	T = _T = 0.0;
	resume();
}

void Timer::stopTiming()
{
	pause();
}

void Timer::pause()
{
	nextFunc = std::bind(&Timer::free, this, _1);
}

void Timer::resume()
{
	Tstart = std::clock();
	nextFunc = std::bind(&Timer::count, this, _1);
}

/////////////////////////////

void Timer::free(Mat& m)
{
}

void Timer::count(Mat& m)
{
	m = img.clone();
	clock_t Tnow = std::clock();
	double dt = 1.0 * (Tnow - Tstart) / CLOCKS_PER_SEC;
	T += dt;

	stringstream sstream;
	sstream << setiosflags(ios::fixed) << setprecision(1) << "Time: " << T << "s";

	putText(m,
			sstream.str(),
			Point(50, 50),
			CV_FONT_HERSHEY_SIMPLEX,
			2,
			Scalar(255, 0, 0)
		);

	Tstart = std::clock();

	if(floor(T) > _T)
	{
		cout << sstream.str() << endl;
		_T = T;
	}
}

/////////////////////////////

void Timer::timThread()
{
	Mat pic;
	Tstart = std::clock();

	while(_flag)
	{
		nowFunc(pic);

		if(nextFunc != nullptr)
		{
			nowFunc = nextFunc;
			nextFunc = nullptr;
		}

		if(pic.data)
		{
			imshow(WIN_TITLE, pic);
			waitKey(1);
		}
	}
}

