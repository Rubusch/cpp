# Makefile for C++ Class
SOURCE	= enum.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -Wno-unused-variable
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

enum.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: enum.exe

clean:
	-${RM} enum.exe *.o core *~

.PHONY: clean
