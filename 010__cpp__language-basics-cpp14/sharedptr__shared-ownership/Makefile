# Makefile for C++ Class
SOURCE	= sharedptr.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

sharedptr.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: sharedptr.exe

clean:
	-${RM} sharedptr.exe *.o *~ core

.PHONY: clean
