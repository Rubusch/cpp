# Makefile for C++ Class
SOURCE	= thread.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

thread.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lpthread -lm

all: thread.exe

clean:
	-${RM} thread.exe *.o core *~

.PHONY: clean
