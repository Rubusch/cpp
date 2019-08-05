# Makefile for C++ Class
SOURCE		= passingfunctionparameter.cpp
HEADERS		=
OBJECTS		= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC			= g++
CPPFLAGS	= -g -Wall -funsigned-char
RM			= rm -f
MV			= mv -f
CP			= cp -f

.c.o:
	${CC} -c ${CPPFLAGS} $<

passingfunctionparameter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: passingfunctionparameter.exe

clean:
	-${RM} passingfunctionparameter.exe *.o core

.PHONY: clean
