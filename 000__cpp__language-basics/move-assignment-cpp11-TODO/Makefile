# Makefile for C++ Class
SOURCE	= moveassignment.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

moveassignment.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: moveassignment.exe

clean:
	-${RM} moveassignment.exe *.o core

.PHONY: clean
