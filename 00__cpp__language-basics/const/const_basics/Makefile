# Makefile for C++ Class
SOURCE	= Main.cpp
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

const.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: const.exe

clean:
	-${RM} const.exe *.o core
