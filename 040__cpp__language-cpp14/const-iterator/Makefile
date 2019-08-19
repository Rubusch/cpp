# Makefile for C++ Class
SOURCE	= const-iterator.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

const-iterator.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: const-iterator.exe

clean:
	-${RM} const-iterator.exe *.o core *~

.PHONY: clean
