# Makefile for C++ Class
SOURCE	= virtual.cpp
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

virtual.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: virtual.exe

clean:
	-${RM} virtual.exe *.o core
