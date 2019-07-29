# Makefile for C++ Class Text Tools
CC = g++
CPPFLAGS = -g -Wall -funsigned-char

start: main.o alpha.o beta.o
	${CC} -o start main.o alpha.o beta.o

main.o: main.cpp
	${CC} -c main.cpp

alpha.o: alpha.cpp alpha.h
	${CC} -c alpha.cpp

beta.o: beta.cpp beta.h
	${CC} -c beta.cpp

all: start

clean :
	rm -f *.o *~ start
