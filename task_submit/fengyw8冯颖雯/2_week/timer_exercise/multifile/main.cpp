#include<iostream>
#include<ctime>//£¿ 
#include<chrono>
#include<ratio>
#include<iomanip>
#include<unistd.h>
#include<string>
#include"Timer.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

using namespace std::chrono; 


int main()
{
	Timer a;
	a.open();
	cout<<"123"<<endl;
	a.startTiming();
	cout<<"123"<<endl;

	//cin>>string;
	//switch
	
	return 0;
}
