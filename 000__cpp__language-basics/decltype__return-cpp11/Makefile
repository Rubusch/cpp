# Makefile for C++ Class
SOURCE	= decltypereturn.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -std=c++11
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

decltypereturn.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: decltypereturn.exe

clean:
	-${RM} decltypereturn.exe *.o core *~

.PHONY: clean
