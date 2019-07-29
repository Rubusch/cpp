# Makefile for C++ Class
SOURCE	= Main.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM		= rm -f
MV		= mv -f
CP		= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

prog.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: prog.exe

clean:
	-${RM} prog.exe *.o core

.PHONY: clean
