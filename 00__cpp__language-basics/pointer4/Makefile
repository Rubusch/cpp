# Makefile for C++ Class
SOURCE	= pointer4.cpp
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

pointer4.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointer4.exe

clean:
	-${RM} pointer4.exe *.o core

.PHONY: clean
