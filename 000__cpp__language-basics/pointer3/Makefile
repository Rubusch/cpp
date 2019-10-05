# Makefile for C++ Class
SOURCE	= pointer3.cpp
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

pointer3.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: pointer3.exe

clean:
	-${RM} pointer3.exe *.o core

.PHONY: clean
