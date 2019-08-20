# Makefile for C++ Class
SOURCE	= alias.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -Wno-unused-local-typedefs
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

alias.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: alias.exe

clean:
	-${RM} alias.exe *.o core *~

.PHONY: clean
