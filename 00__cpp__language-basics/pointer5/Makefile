# Makefile for C++ Class
SOURCE	= pointer5.cpp
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

pointer5.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointer5.exe

clean:
	-${RM} pointer5.exe *.o core

.PHONY: clean
