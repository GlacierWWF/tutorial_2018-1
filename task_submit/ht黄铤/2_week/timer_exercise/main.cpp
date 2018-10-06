#include "Timer.h"
#include <iostream> 
using namespace std;

int main()
{
    Timer t; 	
	char ch[10]; 	
	cout<<"00:00:00";
	while(1)	
	{		
		if(ch=="start")
			t.startTiming();
		if(ch=="stop")
		      t.stopTiming();
	        else if(ch=="quit")
	          t.close();
	        else if(ch=="pause")
		      t.pause();
	        else if(ch=="resume")
	          t.resume();
		if(!t.isstop()&&!t.ispause()) 
		{			
			t.show();	
		}
	}

}
