Timer:Timer.o main.o
	g++ main.o Timer.o -o Timer
main.o:Timer.h main.cpp
	g++ -std=c++11 main.cpp 
Timer.o:Timer.h
	g++ -std=c++11 Timer.cpp 
clean:
	rm -rf *.o Timer
