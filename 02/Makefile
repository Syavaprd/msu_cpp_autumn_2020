CC=g++
OPTS=-c --std=c++14 -O2

all: my_prog

test: my_prog
	./my_prog

my_prog: test.o parser.o
	$(CC) -o my_prog $^

test.o: test.cpp parser.h
	$(CC) test.cpp $(OPTS)

parser.o: parser.cpp
	$(CC) parser.cpp $(OPTS)

clean:
	rm -rf *.o *.dSYM my_prog