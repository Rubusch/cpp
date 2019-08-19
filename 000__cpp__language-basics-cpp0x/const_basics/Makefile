# Makefile for C++ Class
SOURCE	= constbasics.cpp
HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

constbasics.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: constbasics.exe

clean:
	-${RM} constbasics.exe *.o core
