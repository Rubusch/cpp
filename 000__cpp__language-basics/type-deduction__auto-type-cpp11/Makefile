# Makefile for C++ Class
SOURCE	= autotypededuction.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -std=c++11
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

autotypededuction.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: autotypededuction.exe

clean:
	-${RM} autotypededuction.exe *.o core *~

.PHONY: clean
