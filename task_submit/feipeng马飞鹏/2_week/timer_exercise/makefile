INCLUDE = $(shell pkg-config --cflags opencv)
LIBS = $(shell pkg-config --libs opencv)
VPATH = ./src/:./inc/
timer : main.o timer.o
	g++ -o  timer main.o timer.o -I $(INCLUDE) $(LIBS) -lpthread
main.o : main.cpp timer.h
	g++ -c ./src/main.cpp  
timer.o : timer.cpp timer.h
	g++ -c  ./src/timer.cpp
clean :
	rm timer main.o timer.o
