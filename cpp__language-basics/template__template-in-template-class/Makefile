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

template.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: template.exe

clean:
	-${RM} template.exe *.o core
