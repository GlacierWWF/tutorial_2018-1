
timer:timer.o main.o visualise.o
	g++ timer.o main.o visualise.o -o timer
	
timer.o:timer.cpp timer.h
	g++ -std=c++11 timer.cpp 
	
main.o:main.cpp timer.h 
	g++ -std=c++11 main.cpp 

visualise.o:visualise.cpp 
	g++ -c visualise.cpp $(shell pkg-config --cflags opencv)

clean:
	rm -rf *.o
