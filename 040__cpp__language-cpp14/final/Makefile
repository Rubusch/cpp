# Makefile for C++ Class
SOURCE	= final.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

final.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: final.exe

clean:
	-${RM} final.exe *.o core *~

.PHONY: clean
