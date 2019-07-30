# Makefile for C++ Class
SOURCE	= arrayandassert.cpp
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

arrayandassert.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: arrayandassert.exe

clean:
	-${RM} arrayandassert.exe *.o core
