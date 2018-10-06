Timer:main.o Timer.o
	g++ -o Timer main.o Timer.o `pkg-config --libs opencv` -lpthread

main.o:main.cpp Timer.hpp
	g++ -o main.o -c main.cpp

Timer.o:Timer.cpp Timer.hpp
	g++ -o Timer.o -c Timer.cpp
.PHONY:clean
clean:
	rm main.o Timer.o
