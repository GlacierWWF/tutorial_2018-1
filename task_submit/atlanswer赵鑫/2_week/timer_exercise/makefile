CXX = g++
CXXFLAGS += -g -Wall -std=c++14 -pthread $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs opencv)

PROJECT = Timer
EXEC = ./bin/$(PROJECT)
SOURCE = ./src/*.cpp
INCLUDE = ./inc/*.hpp

$(PROJECT): $(SOURCE)
	$(CXX) $(SOURCE) -o $(EXEC) $(CXXFLAGS) $(LDFLAGS)