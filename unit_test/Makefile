SOURCE:=$(wildcard *_test.cc)
OBJ:=$(SOURCE:.cc=.o)
TARGET:=$(SOURCE:.cc=.out)
CXXFLAGS=-O3 -I../engine_race -I..

%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@
%.out: %.o
	g++ $< -o $@ -L../lib -lengine -lpthread -std=c++11
all: $(TARGET)

clean:
	rm -rf *.out *.o
