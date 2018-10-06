CC = g++

main.out: main.cpp op.o
	$(CC)  op.o  main.cpp -o main.out -lpthread `pkg-config --cflags --libs opencv` 

op.o: op.cpp op.h
	$(CC) -c op.cpp op.h

clean: 
	rm *.o  main.out  *.gch


