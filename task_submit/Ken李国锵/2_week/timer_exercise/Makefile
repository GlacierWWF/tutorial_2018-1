
Timer:Timer.o main.o visualise.o
	g++ Timer.o main.o -o Timer
	
Timer.o:Timer.cpp Timer.h
	g++ -std=c++11 Timer.cpp 
	
main.o:main.cpp Timer.h 
	g++ -std=c++11 main.cpp 

visualise.o:visualise.cpp 
	g++ -c visualise.cpp $(shell pkg-config --cflags opencv)

clean:
	rm -rf *.o
