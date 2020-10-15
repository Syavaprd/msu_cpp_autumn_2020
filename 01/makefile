CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: main

main: main.o 
	$(CC) main.o $(FLAGS) -o task

main.o: main.cpp allocator.hpp
	$(CC) $(FLAGS) -c main.cpp

test: 
	./task
