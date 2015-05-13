# Makefile
CC = g++
CPPFLAGS = -g -Wall

Prog: Prog.o
	${CC} -o Prog Prog.o

Prog.o: Prog.cpp
	${CC} -c Prog.cpp

all: Prog

clean: 
	rm *.o Prog
