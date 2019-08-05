# Makefile for C++ Class
SOURCE	= pointer6.cpp
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

pointer6.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointer6.exe

clean:
	-${RM} pointer6.exe *.o core

.PHONY: clean
