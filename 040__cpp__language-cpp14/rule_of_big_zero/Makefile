# Makefile for C++ Class
SOURCE	= ruleofbigzero.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

ruleofbigzero.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: ruleofbigzero.exe

clean:
	-${RM} ruleofbigzero.exe *.o *~ core

.PHONY: clean
