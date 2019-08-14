# Makefile for C++ Class
SOURCE	= auto.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -std=c++11
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

auto.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: auto.exe

clean:
	-${RM} auto.exe *.o core *~

.PHONY: clean
