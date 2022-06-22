all: main

main: GC.o main.o
	g++ -o main.exe GC.o main.o
	
GC.o: GC.cpp GC.h
	g++ -c GC.cpp

main.o: main.cpp
	g++ -c main.cpp
