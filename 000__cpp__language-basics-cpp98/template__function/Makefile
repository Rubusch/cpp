# Makefile for C++ Class
SOURCE	= templatefunction.cpp
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

templatefunction.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templatefunction.exe

clean:
	-${RM} templatefunction.exe *.o core
