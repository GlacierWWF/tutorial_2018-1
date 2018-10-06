objects = ./obj/main.o ./obj/Timer.o

./bin/test : $(objects)
	g++ -o ./bin/test $(objects) \
	-lpthread `pkg-config --cflags --libs opencv`

./obj/main.o : ./main/main.cpp ./inc/Timer.hpp
	g++ -o ./obj/main.o -c ./main/main.cpp -Iinc

./obj/Timer.o : ./src/Timer.cpp ./inc/Timer.hpp
	g++ -o ./obj/Timer.o -c ./src/Timer.cpp -Iinc


.PHONY : clean
clean:
	rm ./bin/test $(objects)
