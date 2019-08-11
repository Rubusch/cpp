# Makefile for C++ Class
SOURCE	= typededuction.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -std=c++11
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

typededuction.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: typededuction.exe

clean:
	-${RM} typededuction.exe *.o core

.PHONY: clean
