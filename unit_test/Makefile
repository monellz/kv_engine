SOURCE:=$(wildcard *_test.cc)
OBJ:=$(SOURCE:.cc=.o)
TARGET:=$(SOURCE:.cc=.out)
CXXFLAGS=-O3 -I../engine_race
%.o: %.cc
	g++ $(CXXFLAGS) -c $< -o $@
%.out: %.o
	g++ $< -o $@
all: $(TARGET)

clean:
	rm -rf *.out *.o
