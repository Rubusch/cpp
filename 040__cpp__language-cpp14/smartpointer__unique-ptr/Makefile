# Makefile for C++ Class
SOURCE	= uniqueptr.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

uniqueptr.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: uniqueptr.exe

clean:
	-${RM} uniqueptr.exe *.o *~ core

.PHONY: clean
