# Makefile for C++ Class
SOURCE	= constexpr.cpp
#HEADERS	=
OBJECTS	= ${SOURCE:.c=.o}

.PREFIXES	= .c .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror -Wno-unused-variable
RM		= rm -f

.c.o:
	${CC} ${CPPFLAGS} -c $<

constexpr.exe: ${OBJECTS}
	${CC} ${CPPFLAGS} -o $@ ${OBJECTS} -lm

all: constexpr.exe

clean:
	-${RM} constexpr.exe *.o core *~

.PHONY: clean
