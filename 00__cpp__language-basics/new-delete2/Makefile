# Makefile for C++ Class
SOURCE	= newdelete2.cpp
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

newdelete2.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: newdelete2.exe

clean:
	-${RM} newdelete2.exe *.o core
