# Makefile for C++ Class
SOURCE	= ruleofbigfive.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

ruleofbigfive.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: ruleofbigfive.exe

clean:
	-${RM} ruleofbigfive.exe *.o core

.PHONY: clean
