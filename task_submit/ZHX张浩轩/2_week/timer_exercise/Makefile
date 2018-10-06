task.out: main.o Timer.o
	g++ Timer.o main.o -lpthread -o task.out `pkg-config --cflags --libs opencv`
main.o: main.cpp Timer.h
	g++ -c main.cpp -lpthread -o main.o `pkg-config --cflags --libs opencv`
Timer.o: Timer.cpp Timer.h
	g++ -c Timer.cpp -lpthread -o Timer.o `pkg-config --cflags --libs opencv`

clean:
	rm main.o Timer.o
