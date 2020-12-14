all: test

test1.o:
	g++ -c test1.cpp

test2.o:
	g++ -c test2.cpp

test3.o:
	g++ -c test3.cpp

test1: test1.o
	g++ -o test1 test1.o

test2: test2.o
	g++ -o test2 test2.o

test3: test3.o
	g++ -o test3 test3.o

test: test1 test2 test3
	./test1
	./test2
	./test3

clean:
	rm -rf *.h.gch format
	rm -rf *.o format
	rm test1 test2 test3