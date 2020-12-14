all: test

test: test.o
	g++ -o test test.cpp
	./test

clean:
	-rm test test.o 
	-rm -rf *.h.gch