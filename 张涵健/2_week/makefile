INCLUDES = -I/usr/local/include/opencv -I.
LIBS = -L/usr/local/lib \
	-lopencv_core \
	-lopencv_imgproc \
	-lopencv_highgui \
	-lopencv_imgcodecs

CXXFLAGS = -g -Wall -o0
OUTPUT = process
HEADERS = timer_client.h

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp = .o)
CXX = g++

all:$(OUTPUT)
$(OUTPUT) : $(OBJS)
	$(CXX) -std=c++11 $^ -o $@ $(INCLUDES) $(LIBS)

%.o : %.cpp $(HEADERS)
	$(CXX) -std=c++11 -c $< $(CXXFLAGS)

.PHONY:clean
clean:
	rm -rf *.out *.oprocess
