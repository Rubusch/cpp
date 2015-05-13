# Makefile
CC = g++
CPPFLAGS = -g -Wall -funsigned-char

Prog: main.o sort.o swap.o
	${CC} -o Prog main.o sort.o swap.o

main.o: main.cpp
	${CC} -c main.cpp

sort.o: sort.cpp sort.h
	${CC} -c sort.cpp

swap.o: swap.cpp swap.h
	${CC} -c swap.cpp

all: Prog

clean: 
	rm *.o Prog
