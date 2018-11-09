CC = g++

./bin/test: ./obj/main.o  ./obj/matrix.o
	$(CC) ./obj/main.o  ./obj/matrix.o -o ./bin/test

./obj/main.o: ./main/main.cpp ./inc/matrix.h
	$(CC) -o ./obj/main.o -c  ./main/main.cpp  -Iinc

./obj/matrix.o: ./src/matrix.cpp  ./inc/matrix.h
	$(CC)  -o ./obj/matrix.o -c ./src/matrix.cpp  -Iinc


clean:
	rm  ./bin/test  ./obj/main.o  ./obj/matrix.o
