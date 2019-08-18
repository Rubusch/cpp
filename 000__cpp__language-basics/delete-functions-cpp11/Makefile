# Makefile for C++ Class
SOURCE	= delete.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

delete.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: delete.exe

clean:
	-${RM} delete.exe *.o core *~

.PHONY: clean
