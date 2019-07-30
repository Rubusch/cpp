# Makefile for C++ Class
SOURCE	= pointer7.cpp
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

pointer7.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointer7.exe

clean:
	-${RM} pointer7.exe *.o core

.PHONY: clean
