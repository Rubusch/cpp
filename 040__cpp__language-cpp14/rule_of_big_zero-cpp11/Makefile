# Makefile for C++ Class
SOURCE	= ruleofbigzero.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

ruleofbigzero.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ruleofbigzero.exe

clean:
	-${RM} ruleofbigzero.exe *.o *~ core

.PHONY: clean
