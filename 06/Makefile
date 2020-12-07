CC=g++

all: test


test1.o:
	$(CC) -c test1.cpp

test2.o:
	$(CC) -c test2.cpp

test3.o:
	$(CC) -c test3.cpp

test1: test1.o
	$(CC) -o test1 test1.o

test2: test2.o
	$(CC) -o test2 test2.o

test3: test3.o
	$(CC) -o test3 test3.o

test: test1 test2 test3
	./test1
	./test2
	./test3

clean:
	rm -rf *.h.gch format
	rm -rf *.o format
	rm test1 test2 test3