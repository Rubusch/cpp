# Makefile for C++ Class Text Tools
CC = g++
CPPFLAGS = -g -Wall

Start: Start.o
	${CC} -o Start Start.o

Start.o: Start.cpp Start.h
	${CC} -c Start.cpp

all: Start

clean :
	rm *.o Start
