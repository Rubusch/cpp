# Makefile for C++ Class
SOURCE	= initializer.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -Wno-unused-variable
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

initializer.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: initializer.exe

clean:
	-${RM} initializer.exe *.o core *~

.PHONY: clean
