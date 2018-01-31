# Makefile
CC = g++
CPPFLAGS = -g -Wall -funsigned-char

Prog: Prog.o
	${CC} -o Prog Prog.o

Prog.o: Prog.cpp
	${CC} -c Prog.cpp

all: Prog

clean:
	rm *.o Prog
