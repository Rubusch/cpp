# Makefile for C++ Class
SOURCE	= templateclass.cpp
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

templateclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templateclass.exe

clean:
	-${RM} templateclass.exe *.o core
