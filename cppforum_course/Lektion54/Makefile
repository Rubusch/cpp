# Makefile for C++ Class
SOURCE	= main.cpp rational.cpp
HEADERS	= rational.h
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

prog: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: prog

clean: 
	-${RM} prog *.o core
