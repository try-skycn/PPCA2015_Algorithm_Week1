CC = c++
CFLAGS = -O2

all: main

main: main.cpp random.o constant.h random.h
	g++ -o main main.cpp random.o -I. $(CFLAGS)

random.o: random.cpp random.h
	g++ -c random.cpp $(FLAGS)

.PHONY: clean

clean:
	rm -f *.o